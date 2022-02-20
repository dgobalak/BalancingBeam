import serial
import time

arduino = serial.Serial(port='COM4', baudrate=115200, timeout=.1)


def write_read(x):
    data = arduino.write(bytes(str(x), "utf-8"))
    time.sleep(0.5)
    return data


while True:
    num = float(input("Enter a number: "))  # Taking input from user
    value = write_read(num)
    print(value)
