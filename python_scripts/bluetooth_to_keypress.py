import time
import pyautogui
import logging
import asyncio
import platform
import time
import uuid

import Adafruit_BluefruitLE
from bleak import BleakClient
from bleak import _logger as logger
logging.basicConfig()

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




# Enable debug output.
#logging.basicConfig(level=logging.DEBUG)

SERVICE_UUID = uuid.UUID('d9c0fc91-b16e-4517-94a5-65eb152ccd44')
CHAR_UUID    = uuid.UUID('88f72c4d-4632-4dc6-81d8-6d5afa20e03a')

import sys

import bluetooth

if len(sys.argv) < 2:
    print("Usage: sdp-browse.py <addr>")
    print("   addr - can be a bluetooth address, \"localhost\", or \"all\"")
    sys.exit(2)

target = sys.argv[1]
if target == "all":
    target = None

services = bluetooth.find_service(address=target)

if len(services) > 0:
    print("Found {} services on {}.".format(len(services), sys.argv[1]))
else:
    print("No services found.")

for svc in services:
    print("\nService Name:", svc["name"])
    print("    Host:       ", svc["host"])
    print("    Description:", svc["description"])
    print("    Provided By:", svc["provider"])
    print("    Protocol:   ", svc["protocol"])
    print("    channel/PSM:", svc["port"])
    print("    svc classes:", svc["service-classes"])
    print("    profiles:   ", svc["profiles"])
    print("    service id: ", svc["service-id"])
