#pragma config(Sensor, S1,     US,             sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          leftWheel,         tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          rightWheel,          tmotorEV3_Large, PIDControl, encoder)

/* Demo day para.(adjustable) */
// Robot Orientation (Facing direction)
int robotDirection=0; // 0=North, 1=East, 2=South, 3=West

// Start in the (0,0) Cell (Starting position)
int startPosRow=0;
int startPosCol=0;

// finish/goal cell
int targetPosRow=3;
int targetPosCol=0;

/* func. declarations */
// EV3 Screen
void gridInit();
void wallGen();
void gridDraw();
void drawBot();
void displayStartandEnd();
void screenRefresh();

// EV3 Screen and/or physical robot
void turnLeft();
void turnRight();
void moveFwd();
void rightWallFollow();
void resetEncoders();

void adjust();
void shortestPath();

/* Global var. */
// EV3 Screen Dimension
const int screenHeight =127;
const int screenWidth  =177;

// Maze Dimension (in rows # and cols #)
const int mazeRow = 4;
const int mazeCol = 6;

// current robot position
int currentPosRow = startPosRow;
int currentPosCol = startPosCol;

// temporary robot position (for right wall follower)
int tempPosRow = mazeRow + 1;
int tempPosCol = mazeCol + 1;

// other para.
int waitTime = 1500;
int wallDist = 5;
int travelDist = 500;
float speed = -20;
int directionHistory[100];
int tempHistory[100];
int directionCounter = 0;

/* Cell Structure datatype */
typedef struct{
	int northWall;
	int eastWall;
	int southWall;
	int westWall;
}cell;

cell grid[mazeRow][mazeCol]; // defining each cell in the maze

/* main func. */
task main()
{
	//set up first
	gridInit();
	wallGen();
	displayStartandEnd();

	// basic movement in EV3 screen (based on sample code starting conditions: line 7 ~ 17)
	gridDraw();
	drawBot();

	// start solving
	while ((currentPosRow != targetPosRow) || (currentPosCol != targetPosCol)){
		rightWallFollow();
	}

	// back to Start using the shortest path
	shortestPath();
}

/* Func. defn's */
// right wall follower for actual bot (works for irl and remote screen)
void rightWallFollow(){
	if ((currentPosRow != tempPosRow) || (currentPosCol != tempPosCol)) {
		turnRight(); // check for wall on the RHS
		tempPosRow = currentPosRow;
		tempPosCol = currentPosCol;
	}
	else{
		// wall detected irl?
		if (SensorValue[US] <= wallDist) {
			if (robotDirection == 0){ // north wall there?
				grid[currentPosRow][currentPosCol].northWall = 1;
				adjust();
				turnLeft();
			}
			else if (robotDirection == 1){ // east wall there?
				grid[currentPosRow][currentPosCol].eastWall = 1;
				adjust();
				turnLeft();
			}
			else if (robotDirection == 2){ // south wall there?
				grid[currentPosRow][currentPosCol].southWall = 1;
				adjust();
				turnLeft();
			}
			else { // west wall there?
				grid[currentPosRow][currentPosCol].westWall = 1;
				adjust();
				turnLeft();
			}
		}

		// no wall detected
		else {
			moveFwd();
			resetEncoders();

			// for shortest way back
			directionHistory[directionCounter] = robotDirection; // keeps track of bot's entire movement history
			directionCounter++; // index for the array above
		}
	}
}

//move bot to center of the cell as long as there is a wall directly in front
void adjust(){
	wait1Msec(waitTime);
	while (getUSDistance(US)>wallDist){
		setMotorSpeed(leftWheel, speed);
		setMotorSpeed(rightWheel, speed);
	}
	while (getUSDistance(US)<wallDist){
		setMotorSpeed(leftWheel, -speed);
		setMotorSpeed(rightWheel, -speed);
	}
	setMotorSpeed(leftWheel, 0);
	setMotorSpeed(rightWheel, 0);
}

// shortest way back to the start
void shortestPath(){
	bool doubleCounter = false; // to find another dead end after finding the first one
	int doubleDiff = 3; // for finding dead end
	int trueCounter = 0; // for finding the size of the shortest path array

	// finds deadend in the entire direction history
	for (int i = 0; i < directionCounter + 1; i++){
		// checking with the previous index
		if (doubleCounter == true){
			// another deadend found after
			if (abs(directionHistory[i + doubleDiff] - directionHistory[i]) == 2) {
				directionHistory[i] = 100;
				directionHistory[i + doubleDiff] = 100;
				i--; // check with previous index
				doubleDiff += 2; // to find another dead end after going one index back
			}

			else { // no more dead end found
				doubleCounter = false;
				doubleDiff = 3;
			}
		}

		// deadend found
		else {
			if(abs(directionHistory[i+1] - directionHistory[i]) == 2){
				doubleCounter = true; // another deadend found
				directionHistory[i] = 100;
				directionHistory[i+1] = 100;
				i--; // check with previous index
			}
		}
	}

	// eliminates the deadend
	for (int i = 0; i < directionCounter + 1; i++){
		// stores the shortest path direction
		if (directionHistory[i] < 4)
		{
			tempHistory[trueCounter] = directionHistory[i];
			trueCounter++;
		}
	}

	// reverses the direction to find the way back (End -> Start)
	int wayBack[trueCounter];
	for (int i = 0; i < trueCounter + 1; i++)
	{
		wayBack[i] = tempHistory[trueCounter - i];
	}
}

// refresh screen every time bot moves
void screenRefresh(){
	eraseDisplay();
	gridDraw();
	displayStartandEnd();
	drawBot();
}

// moves forward
void moveFwd(){
	// Physical robot
	moveMotorTarget(leftWheel, -travelDist, speed);
	moveMotorTarget(rightWheel, -travelDist, speed);
	waitUntilMotorStop(leftWheel);
	waitUntilMotorStop(rightWheel);

	wait1Msec(waitTime);

	// EV3 Screen
	if (robotDirection == 0){ // facing North (0)
		currentPosRow++;
	}
	else if (robotDirection == 1){ // facing East (1)
		currentPosCol++;
	}
	else if (robotDirection == 2){ // facing South (2)
		currentPosRow--;
	}
	else currentPosCol--; // facing West (3)

	screenRefresh(); // erases previous position after moving fwd
}

// turn right
void turnRight(){
	// physical robot
	setMotorTarget(leftWheel,-177.5, speed); // Around 355 deg wheel rotation = 90 deg bot turn
	setMotorTarget(rightWheel,177.5,speed);

	waitUntilMotorStop(leftWheel);
	waitUntilMotorStop(rightWheel);

	resetEncoders();

	wait1Msec(waitTime);

	// EV3 screen
	if (robotDirection == 3){ // facing West (3)
		robotDirection = 0;	// faces North (0)
	}
	else robotDirection++; // turn right

	drawBot(); // rebuild the robot in EV3 screen
}

// turn left
void turnLeft(){
	// physical robot
	setMotorTarget(leftWheel,177.5, speed); // Around 355 deg wheel rotation = 90 deg bot turn
	setMotorTarget(rightWheel,-177.5,speed);

	waitUntilMotorStop(leftWheel);
	waitUntilMotorStop(rightWheel);

	resetEncoders();

	wait1Msec(waitTime);

	// EV3 screen
	if (robotDirection == 0){ // facing North (0)
		robotDirection = 3; // faces West (3)
	}
	else robotDirection--; // turn left

	drawBot(); // rebuild the robot in EV3 screen
}

// set motor encoders to 0
void resetEncoders()
{
	resetMotorEncoder(leftWheel);
	resetMotorEncoder(rightWheel);
}

//=====================================================================
void gridInit(){
	for(int row=0;row<mazeRow;row++){
		for(int col=0;col<mazeCol;col++){
			grid[row][col].northWall=0;
			grid[row][col].eastWall=0;
			grid[row][col].westWall=0;
			grid[row][col].southWall=0;
		}
	}
}

//=====================================================================
void wallGen(){
	int row=0;
	int col=0;

	// outer borders - left and right
	for(row=0;row<mazeRow;row++){
		grid[row][0].westWall=1;
		grid[row][mazeCol - 1].eastWall=1;
	}

	// outer borders - north and south
	for(col=0;col<mazeCol;col++){
		grid[0][col].southWall=1;
		grid[mazeRow - 1][col].northWall=1;
	}
}

//=====================================================================
void gridDraw(){
	int XStart=0;
	int YStart=0;
	int XEnd  =0;
	int YEnd  =0;
	for(int row=0;row<mazeRow;row++){
		for(int col=0;col<mazeCol;col++){
			if(grid[row][col].northWall==1){
				XStart= col   *screenWidth/mazeCol;
				YStart=(row+1)*screenHeight/mazeRow;
				XEnd  =(col+1)*screenWidth/mazeCol;
				YEnd  =(row+1)*screenHeight/mazeRow;
				drawLine(XStart,YStart,XEnd,YEnd);
			}
			if (grid[row][col].eastWall==1){
				XStart=(col+1)*screenWidth/mazeCol;
				YStart=(row)*screenHeight/mazeRow;
				XEnd  =(col+1)*screenWidth/mazeCol;
				YEnd  =(row+1)*screenHeight/mazeRow;
				drawLine(XStart,YStart,XEnd,YEnd);
			}
			if (grid[row][col].westWall==1){
				XStart= col   *screenWidth/mazeCol;
				YStart=(row)*screenHeight/mazeRow;
				XEnd  =(col)*screenWidth/mazeCol;
				YEnd  =(row+1)*screenHeight/mazeRow;
				drawLine(XStart,YStart,XEnd,YEnd);
			}
			if(grid[row][col].southWall==1){
				XStart= col   *screenWidth/mazeCol;
				YStart=(row)*screenHeight/mazeRow;
				XEnd  =(col+1)*screenWidth/mazeCol;
				YEnd  =(row)*screenHeight/mazeRow;
				drawLine(XStart,YStart,XEnd,YEnd);
			}
		}
	}
}

//=====================================================================
void drawBot(){
	int robotXpixelPos=0;
	int robotYpixelPos=0;

	if(currentPosCol==0){
		robotXpixelPos=screenWidth/12;
	}
	else{
		robotXpixelPos=(2*currentPosCol+1)*screenWidth/12;
	}

	if(currentPosRow==0){
		robotYpixelPos=screenHeight/8;
	}
	else{
		robotYpixelPos=(2*currentPosRow+1)*screenHeight/8;
	}

	switch(robotDirection){
	case 0: displayStringAt(robotXpixelPos,robotYpixelPos,"^");	break; // Facing North
	case 1: displayStringAt(robotXpixelPos,robotYpixelPos,">"); break; // Facing East
	case 2: displayStringAt(robotXpixelPos,robotYpixelPos,"V"); break; // Facing South
	case 3: displayStringAt(robotXpixelPos,robotYpixelPos,"<"); break; // Facing West
	default: break;
	}
}

//=====================================================================
void displayStartandEnd(){
	int XpixelPos=0;
	int YpixelPos=0;

	if(startPosCol==0){
		XpixelPos=screenWidth/12;
	}
	else{
		XpixelPos=(2*startPosCol+1)*screenWidth/12;
	}

	if(startPosRow==0){
		YpixelPos=screenHeight/8;
	}
	else{
		YpixelPos=(2*startPosRow+1)*screenHeight/8;
	}
	displayStringAt(XpixelPos,YpixelPos,"S");

	if(targetPosCol==0){
		XpixelPos=screenWidth/12;
	}
	else{
		XpixelPos=(2*targetPosCol+1)*screenWidth/12;
	}

	if(targetPosRow==0){
		YpixelPos=screenHeight/8;
	}
	else{
		YpixelPos=(2*targetPosRow+1)*screenHeight/8;
	}
	displayStringAt(XpixelPos,YpixelPos,"E");
}
