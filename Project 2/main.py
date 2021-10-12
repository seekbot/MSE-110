# libraries/imports
from pybricks.ev3devices import Motor, ColorSensor, Ultrasonic Sensor
from pybricks.parameters import Port
from pybricks.tools import wait
from pybricks.robotics import DriveBase
from pybricks.media.ev3dev import SoundFile

# Initializing motors/sensors
leftWheel = Motor(Port.A)
rightWheel = Motor(Port.D)
bot = DriveBase(leftWheel,rightWheel,wheel_diameter = ,axle_track = )

US = UltrasonicSensor(Port.S1)
CS = ColorSensor(Port.S4)

# global var.
blue = 6
green = 12
bgColour = 35

reflection = # light reflection btwn line and table 
LFPK = # constant to speed up correction (trial-n-error)
speed = 100 # bot/wheel speed


# functions
def lineTracking():

# main func.
while (true):
    correction = (reflection - CS.reflection()) * LFPK
    bot.drive(speed,correction)

