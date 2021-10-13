#!/usr/bin/env pybricks-micropython

# libraries/imports
from pybricks.ev3devices import *
from pybricks.parameters import *
from pybricks.tools import wait
from pybricks.robotics import *
from pybricks.media.ev3dev import SoundFile


# Initializing motors/sensors
leftWheel = Motor(Port.A)
rightWheel = Motor(Port.D)
robot = DriveBase(leftWheel,rightWheel,wheel_diameter = 55.5,axle_track = 104)

us = UltrasonicSensor(Port.S1)
us.mode = 'US-DIST-CM'    #put the ultrasonic sensor into distance mode

# global var.
blue = 6
green = 12
bgColour = 35

reflection = int((green + bgColour) / 2) # light reflection btwn line and table 
LFPK = 2 # constant to speed up correction (trial-n-error)
speed = 80 # bot/wheel speed
objectDist = 10
ev3=EV3Brick()

# functions
def lineTracking():
        correction = (reflection - cs.reflection()) * LFPK
        robot.drive(speed,correction)

def twoSecBeep():
    for i in range(0,2):
        ev3.speaker.beep()
        time.sleep(1) # sleep for 1 sec (repeats twice - 2s)

# main func.
while True: #detects obstacle, proceeds to different colour functions
    
    lineTracking()
    float dist_cm = us.value()/10 #change to cm from mm

    if dist_cm <= objectDist : #object detected within 10cm
        twoSecBeep()
        
        if cs.value()<=blue :
        
        elif cs.value()<=green : #if sensor detects a value thats equal to or less than green, 

        else: #if the sensor does not detect a colour value equal to or lower than green, the bot will turn for another colour value

    else: #does not detect obstacle, continues line tracking
        continue
