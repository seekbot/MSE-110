#pragma config(Sensor, S1,     US,             sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     CS,             sensorEV3_Color, modeEV3Color_Color)
#pragma config(Motor,  motorA,          leftWheel,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorD,          rightWheel,    tmotorEV3_Large, PIDControl, driveRight, encoder)
//!!Code automatically generated by 'ROBOTC' configuration wizard               !!//

task main()
{
	repeat(forever)
	{
		displayBigTextLine(1, "Light: %d", getColorReflected(CS));
		sleep(250);
	}
}
