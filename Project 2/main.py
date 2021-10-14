#!/usr/bin/env pybricks-micropython

# libraries/imports
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
# tracks line
def lineTracking():
        correction = (reflection - cs.reflection()) * LFPK
        robot.drive(speed,correction)

# beeps for 2 sec
def twoSecBeep():
    for i in range(0,2):
       ev3.speaker.beep()
       wait(1000) # sleep for 1 sec (repeats twice - 2s)

# stop robot
def stopMoving():
      robot.stop()
      leftWheel.brake()
      rightWheel.brake()

# main func.
while True: #detects obstacle, proceeds to different colour functions
    
    lineTracking()
    dist_cm = us.distance()/10 # from mm to cm

    if dist_cm <= objectDist : #object detected within 10cm
        stopMoving() # stop 
        twoSecBeep() # beep
        
        # obstacle removing in blue
        if cs.reflection() <= blue:
            robot.turn(180)

        # obstacle removing in green
        elif cs.reflection() <= green:  
            while dist_cm > 3: # approaches the block until 3 cm away
                robot.drive(speed, 0) 
                dist_cm = us.distance()/10
            stopMoving()
            robot.turn(30)
            robot.straight(500)
            robot.straight(-500)
            robot.turn(-30)


        else: #if the sensor does not detect a colour value equal to or lower than green, the bot will turn for another colour value

    else: #does not detect obstacle, continues line tracking
        continue