#!/usr/bin/env pybricks-micropython

# libraries/imports
import math
from pybricks.hubs import *
from pybricks.ev3devices import *
from pybricks.parameters import *
from pybricks.tools import wait
from pybricks.robotics import *
from pybricks.media.ev3dev import SoundFile


# Initializing motors/sensors
leftWheel = Motor(Port.A)
rightWheel = Motor(Port.D)
robot = DriveBase(leftWheel,rightWheel,wheel_diameter = 55.5,axle_track = 104)
ev3 = EV3Brick()
us = UltrasonicSensor(Port.S1)
cs = ColorSensor(Port.S4)

# global var.
blue = 6
green = 11
bgColour = 35

threshold = int((green + bgColour) / 2) # light reflection btwn line and table 
deviation = 5.3 # constant to speed up correction (trial-n-error)
speed = 62.5 # bot/wheel speed
objectDist = 10 # obstacle away from sensor

# functions
# reset wheel rotational angle
def resetWheels():
    leftWheel.reset_angle(0)
    rightWheel.reset_angle(0)

# stop robot
def stopMoving():
      robot.stop()
      leftWheel.brake()
      rightWheel.brake()

# tracks line
def lineTracking():
    # tracks line
    correction = (threshold - cs.reflection()) * deviation
    robot.drive(speed,correction)
    
# beeps for 2 sec
def twoSecBeep():
    for i in range(0,2):
       ev3.speaker.beep()
       wait(1000) # sleep for 1 sec (repeats twice - 2s)

# main func.
while True: #detects obstacle, proceeds to different colour functions
    
    lineTracking()
    dist_cm = us.distance() // 10 # from mm to cm

    if dist_cm <= objectDist : #object detected within 10cm
        stopMoving() # stop 
        twoSecBeep() # beep
        
        # turn toward center of line 
        robot.turn(-15)
        wait(1000)

        # obstacle removing in blue
        if cs.reflection() >= blue and cs.reflection() < green:
            robot.turn(180)

        # obstacle removing in green
        if cs.reflection() >= green and cs.reflection() < bgColour:  
            robot.turn(15)
            robot.straight(150)
            robot.turn(30)
            robot.straight(150)
            robot.straight(-150)
            robot.turn(-30)
        #doesn't detect turns little by little to find line
        else:
            robot.turn(3)