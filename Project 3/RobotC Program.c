#pragma config(Sensor, S1,     CS,             sensorEV3_Color)
#pragma config(Motor,  motorA,          leftWheel,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorD,          rightWheel,    tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void wheelMove(float speed)
{
	// trial-n-error the wheel speed
	setMotorSpeed(leftWheel, speed);
	setMotorSpeed(rightWheel, speed);
}
void stopMotors()
{
	setMotorSpeed(leftWheel, 0);
	setMotorSpeed(rightWheel, 0);
}


task main()
{
	while(true)
	{
		datalogDataGroupStart(); // open datalog

		while() //while still detecting barcode
		{
			wheelMove(35) // insert speed var. within ()
			datalogAddValue(getColorReflected(CS)); //add the colour sensor values into datalog
		}

		//stop scanning and moving
		stopMotors;
		datalogDataGroupEnd();

		//change datalog data into csv file for matlab
		writeDebugStreamLine

	}
}
