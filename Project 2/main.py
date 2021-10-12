# libraries/imports
from pybricks.ev3devices import Motor, ColorSensor, Ultrasonic Sensor
from pybricks.parameters import Port
from pybricks.tools import wait
from pybricks.robotics import DriveBase
from pybricks.media.ev3dev import SoundFile
from ev3dev2.sound import Sound

# Initializing motors/sensors
leftWheel = Motor(Port.A)
rightWheel = Motor(Port.D)
bot = DriveBase(leftWheel,rightWheel,wheel_diameter = ,axle_track = )
# axle track: dist btwn pts where two wheels tocuh gnd

US = UltrasonicSensor(Port.S1)
CS = ColorSensor(Port.S4)

# global var.
blue = 6
green = 12
bgColour = 35

reflection = # light reflection btwn line and table 
LFPK = # constant to speed up correction (trial-n-error)
speed = 100 # bot/wheel speed

sound = Sound()
sound.play_file('') # find 'Error alarm.wav' directory


# functions
def lineTracking():

def twoSecBeep():
    for i in range(0,2):
        sound.beep()
        sleep(1) # sleep for 1 sec (repeats twice - 2s)

# main func.
twoSecBeep()

# line tracking (parameters required)
while (true):
    correction = (reflection - CS.reflection()) * LFPK
    bot.drive(speed,correction)

