import time
import pyautogui

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

