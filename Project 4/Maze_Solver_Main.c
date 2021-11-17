#pragma config(Sensor, S1,     US,             sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          right,         tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          left,          tmotorEV3_Large, PIDControl, encoder)
/* Constant global variables */
// EV3 Screen Dimension
const int screenHeight =127;
const int screenWidth  =177;

// Maze Dimension (in rows # and cols #)
const int mazeRow = 4;
const int mazeCol = 6;

// Cell Structure datatype
typedef struct{
	int northWall;
	int eastWall;
	int southWall;
	int westWall;
}cell;

cell grid[4][6];

// Start Facing North
int robotDirection=0; // 0=North, 1=East, 2=South, 3=West

// Start in the 0,0 Cell
int startPosRow=0; // Starting position
int startPosCol=0;

// current robot position
int currentPosRow=startPosRow; // Starting position
int currentPosCol=startPosCol;

// finish/goal
int targetPosRow=3;
int targetPosCol=0;

/* func. declarations */
void gridInit();
void wallGen();
void gridDraw();
void drawBot();
void displayStartandEnd();

/* main func. */
task main()
{
	gridInit();
	wallGen();
	while( (currentPosRow!=targetPosRow) || (currentPosCol!=targetPosCol)){
		//int temp= Solver();
		gridDraw();
		displayStartandEnd();
		drawBot();
		sleep(1000);
		eraseDisplay();
	}

	while(true){
		displayCenteredTextLine(5,"MAZE SOLVED !!");
		sleep(500);
		eraseDisplay();
		sleep(500);
	}

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

	for(row=0;row<mazeRow;row++){
		grid[row][0].westWall=1;
		grid[row][mazeCol - 1].eastWall=1;
	}

	for(col=0;col<mazeCol;col++){
		grid[0][col].southWall=1;
		grid[mazeRow - 1][col].northWall=1;
	}

	// sample maze for testing
	grid[0][0].northWall =1;  grid[1][0].southWall =1;
	grid[0][1].northWall =1;  grid[1][1].southWall =1;
	grid[0][3].eastWall  =1;  grid[0][4].westWall  =1;
	grid[1][2].eastWall  =1;  grid[1][3].westWall  =1;
	grid[1][3].eastWall  =1;  grid[1][4].westWall  =1;
	grid[1][4].eastWall  =1;  grid[1][5].westWall  =1;
	grid[1][5].northWall =1;  grid[2][5].southWall  =1;
	grid[3][0].eastWall  =1;  grid[3][1].westWall  =1;
	grid[3][4].southWall =1;  grid[2][4].northWall  =1;

	for(col=1;col<4;col++){
		grid[2][col].northWall=1;
		grid[2][col].southWall=1;
		grid[3][col].southWall=1;
		grid[1][col].northWall=1;
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
//int Solver(){
//	?????????
//	?????????
//	?????????
//	?????????
//}

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
