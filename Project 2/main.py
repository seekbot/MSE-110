# libraries/imports
import math
import time
from pybricks.ev3devices import *
from pybricks.parameters import *
from pybricks.tools import wait
from pybricks.robotics import *
from pybricks.media.ev3dev import SoundFile
from ev3dev2.sound import Sound

# Initializing motors/sensors
leftWheel = Motor(Port.A)
rightWheel = Motor(Port.D)
robot = DriveBase(leftWheel,rightWheel,wheel_diameter = 55,axle_track = 145)


us = UltrasonicSensor(Port.S1)
cs = ColorSensor(Port.S4)

# global var.
blue = 6
green = 12
bgColour = 35

reflection = int((green + bgColour) / 2) # light reflection btwn line and table 
LFPK = 2 # constant to speed up correction (trial-n-error)
speed = 80 # bot/wheel speed

sound = Sound()
sound.play_file('') # find 'Error alarm.wav' directory


# functions
def lineTracking():
        correction = (reflection - cs.reflection()) * LFPK
        robot.drive(speed,correction)

def twoSecBeep():
    for i in range(0,2):
        sound.beep()
        sleep(1) # sleep for 1 sec (repeats twice - 2s)

# main func.
twoSecBeep()

while True:
    lineTracking()  # line tracking (parameters required)
    

