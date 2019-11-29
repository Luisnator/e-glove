using System;
using Windows.Devices.Bluetooth;
using Windows.Devices.Bluetooth.GenericAttributeProfile;
using Windows.Devices.Enumeration;
using Windows.Storage.Streams;

// This example code shows how you could implement the required main function for a 
// Console UWP Application. You can replace all the code inside Main with your own custom code.

// You should also change the Alias value in the AppExecutionAlias Extension in the 
// Package.appxmanifest to a value that you define. To edit this file manually, right-click
// it in Solution Explorer and select View Code, or open it with the XML Editor.

namespace CXApp
{
    class Program
    {
        static private String serviceuuid = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
        static private String characteristicuuid = "beb5483e-36e1-4688-b7f5-ea07361b26a8";
        static void Main(string[] args)
        {
            Console.WriteLine("Starting");
            // Query for extra properties you want returned
            string[] requestedProperties = { "System.Devices.Aep.DeviceAddress", "System.Devices.Aep.IsConnected" };

            DeviceWatcher deviceWatcher =
                        DeviceInformation.CreateWatcher(
                                BluetoothLEDevice.GetDeviceSelectorFromPairingState(false),
                                requestedProperties,
                                DeviceInformationKind.AssociationEndpoint);

            // Register event handlers before starting the watcher.
            // Added, Updated and Removed are required to get all nearby devices
            deviceWatcher.Added += DeviceWatcher_Added;
            deviceWatcher.Updated += DeviceWatcher_Updated;
            deviceWatcher.Removed += DeviceWatcher_Removed;

            // EnumerationCompleted and Stopped are optional to implement.
            deviceWatcher.EnumerationCompleted += DeviceWatcher_EnumerationCompleted;
            deviceWatcher.Stopped += DeviceWatcher_Stopped;

            // Start the watcher.
            deviceWatcher.Start();

            Console.WriteLine("Press a key to continue: ");
            Console.ReadLine();
        }

        private static void DeviceWatcher_Stopped(DeviceWatcher sender, object args)
        {
            Console.WriteLine("Stopped");
        }

        private static void DeviceWatcher_EnumerationCompleted(DeviceWatcher sender, object args)
        {
            Console.WriteLine("Enum complete");
        }

        private static void DeviceWatcher_Removed(DeviceWatcher sender, DeviceInformationUpdate device)
        {
            
            Console.WriteLine(String.Format("Removed Device with ID: {0}", device.Id));
        }

        private static void DeviceWatcher_Updated(DeviceWatcher sender, DeviceInformationUpdate device)
        {
            Console.WriteLine(String.Format("Updated Device with ID: {0}", device.Id));
        }

        private static void DeviceWatcher_Added(DeviceWatcher sender, DeviceInformation deviceInfo)
        {
            Console.WriteLine(String.Format("Added ID: {0} | Name: {1}", deviceInfo.Id, deviceInfo.Name));
            ConnectDevice(deviceInfo);
        }

        async static void ConnectDevice(DeviceInformation deviceInfo)
        {
            // Note: BluetoothLEDevice.FromIdAsync must be called from a UI thread because it may prompt for consent.
            BluetoothLEDevice bluetoothLeDevice = await BluetoothLEDevice.FromIdAsync(deviceInfo.Id);

            //Console.WriteLine(String.Format("Connected to device:    ID: {0} | Name: {1}", bluetoothLeDevice.DeviceId, bluetoothLeDevice.Name));
            GattDeviceServicesResult result = await bluetoothLeDevice.GetGattServicesAsync();

            if (result.Status == GattCommunicationStatus.Success)
            {
                var services = result.Services;
                for (int i = 0; i < services.Count; i++)
                {
                    //Console.WriteLine(String.Format("Device: {0} | Service: {1}", bluetoothLeDevice.Name, services[i].Uuid));
                    if (services[i].Uuid.Equals(new Guid(serviceuuid)))
                    {
                        SubscribeToServiceAsync(services[i]);
                    }
                }
            }
        }

        async static void SubscribeToServiceAsync(GattDeviceService service)
        {
            Console.WriteLine(String.Format("Subscribing to: {0}", service.Uuid));
            GattCharacteristicsResult result = await service.GetCharacteristicsAsync();

            if (result.Status == GattCommunicationStatus.Success)
            {
                var characteristics = result.Characteristics;

                for (int i = 0; i < characteristics.Count; i++)
                {
                    if (characteristics[i].Uuid.Equals(new Guid(characteristicuuid)))
                    {
                        GattCommunicationStatus status = await characteristics[i].WriteClientCharacteristicConfigurationDescriptorAsync(
                        GattClientCharacteristicConfigurationDescriptorValue.Notify);
                        if (status == GattCommunicationStatus.Success)
                        {
                            Console.WriteLine("Server has been informed of clients interest.");
                        }

                        characteristics[i].ValueChanged += Characteristic_ValueChanged;
                        // ... 

                        
                    }
                }
            }
        }

        static void Characteristic_ValueChanged(GattCharacteristic sender, GattValueChangedEventArgs args)
        {
            // An Indicate or Notify reported that the value has changed.
            var reader = DataReader.FromBuffer(args.CharacteristicValue);
            // Parse the data however required.
            String  value = reader.ReadString(17);
            Console.WriteLine(value);
        }
    }
}
