#pragma config(Sensor, S1,     US,             sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     CS,             sensorEV3_Color)
#pragma config(Motor,  motorA,          leftWheel,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorD,          rightWheel,    tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*In Virtual Worlds,
left wheel - Port 'B'  and right wheel - Port 'C'.
Sonar sensor - Port '4' and Color Sensor - Port '3'.
Our bot:
left wheel - Port 'A' and right wheel  - Port 'D'.
Sonar sensor - Port '1' and Color Sensor - Port '4'*/

/*Global Variables*/

/* Function List */
void twoSecBeep();	 // 2 sec beep
//void stop10();		 // stop 10 cm b4 obj
//void lineTracking(); // move while tracking line

/* main func */
task main()
{
	// set motor encoders to 0
	nMotorEncoder[leftWheel] = 0;
	nMotorEncoder[rightWheel] = 0;

	// line tracking
	while (true)
	{	// to be removed (getColorName(CS) == colorBlack)
		if (getUSDistance(US) <= 10)
		{
			setMotorSpeed(leftWheel, 0);
			setMotorSpeed(rightWheel, 0);
			twoSecBeep();
			// take next actions
		}
		if ((getColorName(CS) == colorBlue) || (getColorName(CS) == colorGreen) || (getColorName(CS) == colorBlack))
		{
			setMotorSpeed(leftWheel, 50);
			setMotorSpeed(rightWheel, 0);

		}
		else if ((getColorName(CS) != colorBlue) || (getColorName(CS) != colorGreen) || (getColorName(CS) != colorBlack))
		{
			setMotorSpeed(leftWheel, 0);
			setMotorSpeed(rightWheel, 50);
		}
	}
}

/* Function Def. */
// 2 sec beep
void twoSecBeep()
{
	for (int i = 1; i < 3; i++)
	{
		playSoundFile("Error alarm");
		sleep(1000);
	}
}
