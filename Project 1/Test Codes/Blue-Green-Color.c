#pragma config(Sensor, S3,     Colour_Sensor,  sensorEV3_Color, modeEV3Color_Color)
task main()
{
	int colourVal;
	int intensity;
while(1)
{
	//intensity = getColorReflected(Colour_Sensor); //If this instruction is put in the program, it makes the sensor flashing and does not work properly.
	//	displayTextLine(3, "%d", intensity);

			//	if(intensity <13)
			//	{
					colourVal = getColorName(Colour_Sensor);

					if(colourVal == 3  )
					{
						displayTextLine(1, "%s,%d","green", colourVal);
					}
					else if(colourVal == 2)
					{
						displayTextLine(1, "%s,%d","blue", colourVal);
					}
					else
					{
						displayTextLine(1, "%s,%d","other", colourVal);
					}
}

}
