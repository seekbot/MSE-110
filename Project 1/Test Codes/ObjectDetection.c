#pragma config(Sensor, S1, US, sensorEV3_Ultrasonic)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Beeping for 2 sec
void twoSecBeep()
{
	for (int i = 1; i < 3; i++)
	{
		playSoundFile("Error alarm");
		sleep(1000);
	}
}

void stop10()
{
	while (true)
	{
		int dist = getUSDistance(US);
		if (dist <= 10)
		{
			twoSecBeep();
			break;
		}
	}
}

task main()
{

	stop10();
}
