import serial
import pyautogui
arduino = serial.Serial('/dev/cu.usbmodem1101', 9600)
def write_read(x):
    data = arduino.readline()
    return data
while True:
    value = str(write_read(1))
    print(value)
    if 'Pause' in value:
        pyautogui.hotkey('right')