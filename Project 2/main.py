# libraries/imports
from pybricks.ev3devices import Motor, ColorSensor
from pybricks.parameters import Port
from pybricks.tools import wait
from pybricks.robotics import DriveBase

# Initializing motors/sensors
leftWheel = Motor(Port.A)
rightWheel = Motor(Port.D)
US = UltrasonicSensor(Port.S1)
CS = ColorSensor(Port.S4)

# global var.
blue = 6
green = 12
bgColour = 35

# functions
def lineTracking():

# main func.
while (true):
