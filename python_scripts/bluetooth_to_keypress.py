import time
import pyautogui
import pygatt
from binascii import hexlify

def doKeypress(input):
    # If "Next Page"
    if input == 1:
        pyautogui.press('right')
    
    # If "Previous Page"
    elif input == 2:
        pyautogui.press('left')
    
    # If "Start Presentation"
    elif input == 3:
        pyautogui.press('f5')
    
    # If "End Presentation"
    elif input == 4:
        pyautogui.press('esc')
    
    # If "Next Track"
    elif input == 5:
        pyautogui.press('nexttrack')
    
    # If "Previous Track"
    elif input == 6:
        pyautogui.press('prevtrack')
    
    # If "Play / Pause"
    elif input == 7 or input == 8:
        pyautogui.press('playpause')
    
    # If "Volume Up"
    elif input == 9:
        pyautogui.press('volumeup')
    
    # If "Volume Down"
    elif input == 10:
        pyautogui.press('volumedown')
    
    # If "Next Website"
    elif input == 11:
        pyautogui.hotkey('alt', 'right')
    
    # If "Previous Website"
    elif input == 12:
        pyautogui.hotkey('alt', 'left')
    
    # If "Scroll Up"
    elif input == 13:
        pyautogui.press('up')
    
    # If "Scroll Down"
    elif input == 14:
        pyautogui.press('down')

adapter = pygatt.BGAPIBackend(serial_port='COM5')
#adapter = pygatt.GATTToolBackend()
value = 0
deviceid = '84:0d:8e:25:a0:aa'     #'16:46:1A:83:19:66'
characteristicid = 'beb5483e-36e1-4688-b7f5-ea07361b26a8'    #"438366C1-9FAE-4B36-9575-71762012041B"

def handle_data(handle, raw_value):
    """
    handle -- integer, characteristic read handle the data was received on
    raw_value -- bytearray, the data returned in the notification
    """
    value = hexlify(raw_value)

try:
    adapter.start()
    device = adapter.connect(deviceid)

    device.subscribe(characteristicid,
                     callback=handle_data)
    while True:
        print("Received data: %s" % value)
finally:
    adapter.stop()