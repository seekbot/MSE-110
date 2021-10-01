#pragma config(Sensor, S1,     US,             sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     CS,             sensorEV3_Color, modeEV3Color_Color)
#pragma config(Motor,  motorA,          leftWheel,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorB,          armMotor,      tmotorEV3_Medium, PIDControl, encoder)
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
void lineTracking(); // move while tracking line

/* main func */
task main()
{
	// set motor encoders to 0
	nMotorEncoder[leftWheel] = 0;
	nMotorEncoder[rightWheel] = 0;

	while (true)
	{

		if (getUSDistance(US) <= 10)
		{
			//obstacle scenario for green line
			if(getColorName(CS)==colorGreen)
			{
				// bot stops
				setMotorSpeed(leftWheel, 0);
				setMotorSpeed(rightWheel, 0);

				twoSecBeep();	// beeps for 2 sec
				while(getUSDistance(US)>=5)
				{
					setMotorSpeed(leftWheel, 10);
					setMotorSpeed(rightWheel,10);
				}
				while (getUSDistance(US) < 5)
				{
					moveMotorTarget(armMotor, 40, -50); // arms down
					sleep(2000);
					moveMotorTarget(armMotor, -80, -50); // arms up
					sleep(2000);
				}
			}
			//obstacle scenario for blue line
			if((getColorName(CS)==colorBlack)||(getColorName(CS)==colorBlue))
			{
				moveMotorTarget(leftWheel, -680, 25);  //vars: motor index, position and speed
				moveMotorTarget(rightWheel, 680, 25);
			}
		}
		//if on color, but no obstacle, continue running
		lineTracking();
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

void lineTracking()
{
	while(true)
	{
		if((getColorName(CS)==colorBlue)||(getColorName(CS)==colorGreen)||(getColorName(CS)==colorBlack))
		{
			setMotorSpeed(leftWheel, 45);
			setMotorSpeed(rightWheel, 0);
		}
		//if no color detected, turn
		else
		{
			setMotorSpeed(leftWheel, 0);
			setMotorSpeed(rightWheel, 45);
		}
	}
}
