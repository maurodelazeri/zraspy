#!/usr/bin/env python3

from gpiozero import Servo
from time import sleep

# Adjust the pulse values to set rotation range
min_pulse = 0.000544    # Library default = 1/1000
max_pulse = 0.0024              # Library default = 2/1000
# Initial servo position
pos = 0
test = 0

servo = Servo(23, pos, min_pulse, max_pulse, 20/1000, None)

def delays(pos):
    if pos == 0:
        print('Stop', pos)
        sleep(0.2)
    elif pos == 1.0:
        print('Full Left', pos)
        sleep(0.2)
    elif pos == -1.0:
        print('Full Right', pos)
        sleep(0.2)
    else:
        print(pos)

while True:
    # For statement example
    for pos in range(0, 20):
        pos = pos * 0.1 - 1
        servo.value = pos
        delays(pos)

    for pos in range(20, -1, -1):
        pos = pos * 0.1 - 1
        servo.value = pos
        delays(pos)
