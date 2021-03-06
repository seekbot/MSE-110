#pragma config(Sensor, S1,     US,             sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     CS,             sensorEV3_Color, modeEV3Color_Color)
#pragma config(Motor,  motorB,          leftWheel,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightWheel,    tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*In Virtual Worlds,
left wheel - Port 'B'  and right wheel - Port 'C'.
Sonar sensor - Port '4' and Color Sensor - Port '3'.

Our bot:
left wheel - Port 'A' and right wheel  - Port 'D'.
Sonar sensor - Port '1' and Color Sensor - Port '4'*/

int wheelSpeed = 50;

void motorControl()
{
	// Reset the encoder to 0
	nMotorEncoder[motorB] = 0; // Change later on
	nMotorEncoder[motorC] = 0;

	while (true)
	{
		motor[motorB] = wheelSpeed;
		motor[motorC] = wheelSpeed;
	}
}

task main()
{
	motorControl();
}
