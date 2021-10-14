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
green = 12
bgColour = 35

reflection = int((green + bgColour) / 2) # light reflection btwn line and table 
LFPK = 2 # constant to speed up correction (trial-n-error)
speed = 80 # bot/wheel speed
objectDist = 12 # obstacle away from sensor

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
    correction = (reflection - cs.reflection()) * LFPK
    robot.drive(speed,correction)
    
    # sharp turns
    if cs.reflection() > bgColour:
        resetWheels()
        stopMoving()
        isLeftExist = False 

        # search for path in left until detected
        while rightWheel.angle() < 720:
            if cs.reflection() <= reflection:
                isLeftExist = True # path exists in left
                break
            rightWheel.run(speed) # keep searching for line in left

        stopMoving()
        resetWheels()

        # search for path in right until detected
        while leftWheel.angle() < 720 and isLeftExist == False: 
            if cs.reflection() <= reflection:
                stopMoving()
                resetWheels()

                robot.turn(45) # re-adjust the position of robot to the track
                resetWheels()
                break

            leftWheel.run(speed/2) # keep searching for the line in right


# beeps for 2 sec
def twoSecBeep():
    for i in range(0,2):
       ev3.speaker.beep()
       wait(1000) # sleep for 1 sec (repeats twice - 2s)

# main func.
while True: #detects obstacle, proceeds to different colour functions
    
    lineTracking()
    dist_cm = us.distance()/10 # from mm to cm

    # if dist_cm <= objectDist : #object detected within 10cm
    #     stopMoving() # stop 
    #     twoSecBeep() # beep
        
    #     # obstacle removing in blue
    #     if cs.reflection() >= blue and cs.reflection() < green:
    #         robot.turn(180)

    #     # obstacle removing in green
    #     elif cs.reflection() >= green and cs.reflection() < bgColour:  
    #         while dist_cm > 3: # approaches the block until 3 cm away
    #             robot.drive(speed, 0) 
    #             dist_cm = us.distance()/10
    #         stopMoving()
    #         robot.turn(30)
    #         robot.straight(500)
    #         robot.straight(-500)
    #         robot.turn(-30)

    #     #else: # colour not detected, reposition to center of tape