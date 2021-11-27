void shortestPath()
{
	bool doubleCounter = false; // to find another dead end after finding the first one and so on...
	int doubleDiff = 3; // for finding another dead end(s)
	// finds deadend in the entire direction history
	for (int i = 0; i < directionCounter - 1; i++)
	{
		// checking with the previous index
		if (doubleCounter == false){
			if(abs(directionHistory[i+1] - directionHistory[i]) == 2){
				doubleCounter = true; // find another deadend(s)
				directionHistory[i] = 100;
				directionHistory[i+1] = 100;
				i--; // check with previous index
			}
		}
		else{
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
	}
	int test=0;
	int trueCounter = 0; // used as an index of the shortest path array

	// eliminates the deadend
	for (int i = 0; i < directionCounter; i++){
		// stores the shortest path direction (Start -> End)
		if (directionHistory[i] < 4){
			tempHistory[trueCounter] = directionHistory[i];
			trueCounter++;
		}
	}
	// reverses the direction to find the way back (End -> Start)
	for (int i = trueCounter - 1; i >= 0 ; i--){
		if (tempHistory[i] == 1){ // from east to west
			wayBack[wayBackIndex] = tempHistory[i] + 2; // stores the reverse direction
			wayBackIndex++; // for indexing
		}
		else{
			wayBack[wayBackIndex] = abs(tempHistory[i] - 2); // stores the reverse direction
			wayBackIndex++; // for indexing
		}
	}
}
