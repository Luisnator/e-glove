using System;
using Windows.Devices.Bluetooth;
using Windows.Devices.Bluetooth.GenericAttributeProfile;
using Windows.Devices.Enumeration;
using Windows.Storage.Streams;
using Windows.UI.Input.Preview.Injection;
using Windows.System;

namespace CXApp
{
    class Program
    {
        static private String serviceuuid = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
        static private String characteristicuuid = "beb5483e-36e1-4688-b7f5-ea07361b26a8";
        static private DeviceWatcher deviceWatcher;
        static void Main(string[] args)
        {
            Console.WriteLine("Starting");

            setup();

            Console.WriteLine("Press a key to continue: ");
            Console.ReadLine();
        }
        private static void setup()
        {
            // Query for extra properties you want returned
            string[] requestedProperties = { "System.Devices.Aep.DeviceAddress", "System.Devices.Aep.IsConnected" };

            deviceWatcher =
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

            Console.WriteLine(String.Format("Connected to device:    ID: {0} | Name: {1}", bluetoothLeDevice.DeviceId, bluetoothLeDevice.Name));
            GattDeviceServicesResult result = await bluetoothLeDevice.GetGattServicesAsync();

            if (result.Status == GattCommunicationStatus.Success)
            {
                var services = result.Services;
                for (int i = 0; i < services.Count; i++)
                {
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
                        try
                        {
                            GattCommunicationStatus status = await characteristics[i].WriteClientCharacteristicConfigurationDescriptorAsync(
                            GattClientCharacteristicConfigurationDescriptorValue.Notify);
                            if (status == GattCommunicationStatus.Success)
                            {
                                Console.WriteLine("Server has been informed of clients interest.");
                            }

                            characteristics[i].ValueChanged += Characteristic_ValueChanged;
                        }
                        catch
                        {
                            Console.WriteLine("Error during subscription.");
                            deviceWatcher.Stop();
                            setup();

                        }


                    }
                }
            }
        }

        static void Characteristic_ValueChanged(GattCharacteristic sender, GattValueChangedEventArgs args)
        {
            // An Indicate or Notify reported that the value has changed.
            var reader = DataReader.FromBuffer(args.CharacteristicValue);
            // Parse the data
            int value = reader.ReadInt16() >> 8;
            Console.WriteLine(String.Format("Value read: {0}", value));
            GenerateKeypress(value);
        }
 
        static void GenerateKeypress(int val)
        {
            InputInjector inputInjector = InputInjector.TryCreate();
            var info = new InjectedInputKeyboardInfo();

            switch (val)
            {
                case 1: //Next Page (Presentation)
                    Console.WriteLine("RIGHT / NEXT PAGE (Presentation)");
                    info = new InjectedInputKeyboardInfo();
                    info.VirtualKey = (ushort) VirtualKey.Right;
                    inputInjector.InjectKeyboardInput(new[] { info });
                    break;
                case 2: //Previous Page (Presentation)
                    Console.WriteLine("LEFT / PREVIOUS PAGE (Presentation)");
                    info = new InjectedInputKeyboardInfo();
                    info.VirtualKey = (ushort) VirtualKey.Left;
                    inputInjector.InjectKeyboardInput(new[] { info });
                    break;
                case 3: //Start Presentation (F5)
                    Console.WriteLine("F5");
                    info = new InjectedInputKeyboardInfo();
                    info.VirtualKey = (ushort)VirtualKey.F5;
                    inputInjector.InjectKeyboardInput(new[] { info });
                    break;
                case 4: //End Presentation (Esc)
                    Console.WriteLine("ESC");
                    info = new InjectedInputKeyboardInfo();
                    info.VirtualKey = (ushort)VirtualKey.Escape;
                    inputInjector.InjectKeyboardInput(new[] { info });
                    break;
                case 5: //Next Track
                    Console.WriteLine("NEXT TRACK");
                    info = new InjectedInputKeyboardInfo();
                    info.VirtualKey = (ushort)176;
                    inputInjector.InjectKeyboardInput(new[] { info });
                    break;
                case 6: //Previous Track
                    Console.WriteLine("PREVIOUS TRACK");
                    info = new InjectedInputKeyboardInfo();
                    info.VirtualKey = (ushort)177;
                    inputInjector.InjectKeyboardInput(new[] { info });
                    break;
                case 7: //Play / Pause
                    Console.WriteLine("PLAY / PAUSE");
                    info = new InjectedInputKeyboardInfo();
                    info.VirtualKey = (ushort)179;
                    inputInjector.InjectKeyboardInput(new[] { info });
                    break;
                case 8: //Volume Up
                    Console.WriteLine("Volume UP");
                    info = new InjectedInputKeyboardInfo();
                    info.VirtualKey = (ushort)175;
                    inputInjector.InjectKeyboardInput(new[] { info });
                    break;
                case 9: //Volume Down
                    Console.WriteLine("Volume DOWN");
                    info = new InjectedInputKeyboardInfo();
                    info.VirtualKey = (ushort)174;
                    inputInjector.InjectKeyboardInput(new[] { info });
                    break;
                case 10: //Next Page (Browser)
                    Console.WriteLine("NEXT PAGE (Browser)");
                    info = new InjectedInputKeyboardInfo();
                    info.VirtualKey = (ushort)167;
                    inputInjector.InjectKeyboardInput(new[] { info });
                    break;
                case 11: //Previous Page (Browser)
                    Console.WriteLine("PREVIOUS PAGE (Browser)");
                    info = new InjectedInputKeyboardInfo();
                    info.VirtualKey = (ushort)166;
                    inputInjector.InjectKeyboardInput(new[] { info });
                    break;
                case 12: //Scroll Up
                    Console.WriteLine("UP");
                    info = new InjectedInputKeyboardInfo();
                    info.VirtualKey = (ushort)VirtualKey.Up;
                    inputInjector.InjectKeyboardInput(new[] { info });
                    break;
                case 13: //Scroll Down
                    Console.WriteLine("DOWN");
                    info = new InjectedInputKeyboardInfo();
                    info.VirtualKey = (ushort)VirtualKey.Down;
                    inputInjector.InjectKeyboardInput(new[] { info });
                    break;
                default:
                    Console.WriteLine("Invalid code read!");
                    break;
            }
        }
    }
}
