void motorSpeed(speed)
{
	// trial-n-error the wheel speed
	setMotorSpeed(nMotorIndex, speed);
	setMotorSpeed(nMotorIndex, speed);
}


task main()
{
	motorSpeed() // insert speed var. within ()

}
