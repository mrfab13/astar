#include <iostream>
#include <ctime>
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <conio.h>
#include <array>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

//27.3.19 - 22.4.19
//Vaughan Webb
//input - X and Y positions - 2x integers
//moves the cursors porition to the passed x and y values
void gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//27.3.19 - 25.4.19
//Vaughan Webb
//input - a string and integer for what color - 1x string, 1x integers
//chnages the color of a string to a spefified color and prints it to the screen
void  ColoredText(string m_word, int m_color) 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), m_color);
	cout << m_word;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}



#pragma region "Anneal"

//global variables
float StartingTemp = 10;
float FinalTemp = 0.1;
float CurrentTemp = StartingTemp;

//declearing function as written in hillclimb but used in anneal also
void RandomGrid(int *board, int QueenNo);
void BoardPrint(int *board, int QueenNo);
int Collisions(int *board, int QueenNo);

int* generateGridAnneal(int *board, int QueenNo)
{
	vector<int> placement;
	int place = Collisions(board, QueenNo);

	int newPlace;
	int* gridOut;
	gridOut = new int[QueenNo];


	for (int i = 0; i < QueenNo; i++)
	{
		gridOut[i] = board[i];
	}

	while (CurrentTemp > FinalTemp) 
	{
		for (int i = 0; i < QueenNo; i++)
		{
			placement.clear();
			placement.push_back(gridOut[i]);
			for (int j = 0; j < QueenNo; j++)
			{
				gridOut[i] = j;
				newPlace = Collisions(gridOut, QueenNo);
				int deltaC = newPlace - place;
				float randno = (rand() / (float)RAND_MAX * 1);

				if (deltaC < 0)
				{
					placement.clear();
					placement.push_back(j);
					place = newPlace;
				}
				else if (randno > 1-(exp(-(deltaC / CurrentTemp))))
				{
					placement.push_back(j);
				}
			}
			gridOut[i] = placement[rand() % placement.size()];
			if (Collisions(gridOut, QueenNo) == 0)
			{
				break;
			}
		}
		CurrentTemp = CurrentTemp - 0.03;

		system("cls");
		BoardPrint(gridOut, QueenNo);
		cout << CurrentTemp << endl;



	}
	return (gridOut);
}


bool NextBoardAnneal(int *board, int QueenNo)
{
	bool test = false;
	int *Board2 = generateGridAnneal(board, QueenNo);

	if (Collisions(Board2, QueenNo) < Collisions(board, QueenNo))
	{
		for (int p = 0; p < QueenNo; p++)
		{
			board[p] = Board2[p];
		}
		test = true;
	}
	return (test);
}


void AnnealSetup(int QueenNo)
{
	int count = 0;
	int *board = new int[QueenNo];

	while (Collisions(board, QueenNo) != 0)
	{
		count++;
		if (NextBoardAnneal(board, QueenNo) == false)
		{
			cout << "objective not reached";
			BoardPrint(board, QueenNo);
			system("pause");
			CurrentTemp == StartingTemp;
			RandomGrid(board, QueenNo);

		}

	}
	//displays a message with information on how many itterations it took and then prints the final boardstate
	cout << endl << "After " << count << " itterations the final boardstate is:" << endl << endl;
	BoardPrint(board, QueenNo);
	cout << endl;
	 StartingTemp = 1000;
	 FinalTemp = 10;
	 CurrentTemp = StartingTemp;
	system("pause");
}

#pragma endregion 

#pragma region "hillclimb"

//27.3.19 - 24.4.19
//Vaughan Webb
//input - pointer to the boards array and the number of queens - 2x integers
//generates a random number for each of the queens position 
void RandomGrid(int *board, int QueenNo)
{
	//for each queen
	for (int i = 0; i < QueenNo; i++) 
	{
		//random placement of the queens
		board[i] = rand() % QueenNo;
	}

}

//27.3.19 - 24.4.19
//Vaughan Webb
//input - pointer to the boards array and the number of queens - 2x integers
//Checks to see if the queens have any collisions from their current board position
int Collisions(int *board, int QueenNo) 
{
	//initlizing
	int hit = 0;

	//loop for first dimention
	for (int x = 0; x < QueenNo - 1; x++) 
	{
		//loop for second dimention
		for (int y = x + 1; y < QueenNo; y++) 
		{
			//checks vertical aliignment for collisions
			if (board[x] == board[y]) 
			{
				hit++;
			}
			//checks "\" angled collisions
			if (board[x] - board[y] == x - y)
			{
				hit++;
			}
			//checks for "/" angled collisions
			if (board[x] - board[y] == y - x) 
			{
				hit++;
			}
		}
	}
	//return how many collisions occured
	return (hit);
}

//27.3.19 - 24.4.19
//Vaughan Webb
//input - pointer to the boards array and the number of queens - 2x integers
//prints the grid onto the console
void BoardPrint(int *board, int QueenNo)
{
	//prints how many collisions the current board has
	cout << endl;
	cout << "collisions: " << Collisions(board, QueenNo) <<endl;

	//2 for loops to display on the x and y axis
	for (int i = 0; i < QueenNo; i++)
	{
		for (int j = 0; j < QueenNo; j++)
		{
			//if a queen is at this location place a O
			if (j == board[i])
			{
				cout << "O";
			}
			//if its not print a +
			else
			{
				ColoredText("+", 13);
			}
		}
		cout << endl;
	}
}

//27.3.19 - 24.4.19
//Vaughan Webb
//input - pointer to the boards array and the number of queens - 2x integers
//generates the next boardstate for comparison
int* CreateNextBoard(int *board, int QueenNo)
{
	//initlising variables
	vector<int> storage;
	int collisionsOG = Collisions(board, QueenNo);
	int collisionsTemp = 0;
	int *board2 = new int[QueenNo];

	//copys the current one onto the blank one for alterations
	for (int i = 0; i < QueenNo; i++) 
	{
		board2[i] = board[i];
	}

	//loop for first axis
	for (int i = 0; i < QueenNo; i++) 
	{
		//reset for new row
		storage.clear();
		storage.push_back(board2[i]);

		//loop for second axis
		for (int j = 0; j < QueenNo; j++) 
		{
			//change the current board
			board2[i] = j;
			//test for how many collisions occur 
			collisionsTemp = Collisions(board2, QueenNo);

			//if the generated one is the same as the old one 
			if (collisionsTemp == collisionsOG)
			{
				//save it
				storage.push_back(j);
			}
			//if the generated on is better then the old one
			if (collisionsTemp < collisionsOG)
			{
				//clear it and save the new best one and replase the comparison value with the new one
				storage.clear();
				storage.push_back(j);
				collisionsOG = collisionsTemp;
			}
		}
		//adds the best queen for its row to the new board
		board2[i] = storage.at(rand() % storage.size());
	}
	//return the new boardstate
	return (board2);
}

//27.3.19 - 24.4.19
//Vaughan Webb
//input - pointer to the boards array and the number of queens - 2x integers
//finds the next best boardstate
bool NextBoardState(int *board, int QueenNo) 
{
	//initilising variables and a seconds board
	int *tempBoard = CreateNextBoard(board, QueenNo);
	BoardPrint(tempBoard, QueenNo);
	bool test = false;

	//if the secound board is better then the first one 
	if (Collisions(tempBoard, QueenNo) < Collisions(board, QueenNo))
	{
		//chnage the value of test
		test = true;

		//replace all the values in the old one with the new one
		for (int i = 0; i < QueenNo; i++)
		{
			board[i] = tempBoard[i];
		}
	}
	//return either true or false depending if the boardstate was altered or not
	return (test);
}

//27.3.19 - 24.4.19
//Vaughan Webb
//input - the number of queens being placed - 1x integer
//Calls the functions to perform hillclimbing and shows the final result
void HillClimbSetup(int QueenNo)
{
	//initlizing variables
	int* board = new int[QueenNo];
	RandomGrid(board, QueenNo);
	bool test;
	int count = 0;

	//loop while problem is not sloved
	while (Collisions(board, QueenNo) != 0)
	{
		//finds the next itteration of the board 
		test = NextBoardState(board, QueenNo);
		//if its unsolvable reset the board back to a random one
		if (test == false) 
		{
			RandomGrid(board, QueenNo);
		}
		//adds to the ittaration counter
		count++;

	}
	//displays a message with information on how many itterations it took and then prints the final boardstate
	cout << endl << "After " << count << " itterations the final boardstate is:" << endl << endl;
	BoardPrint(board, QueenNo);
	cout << endl;
	system("pause");
}

#pragma endregion

#pragma region "a*"

//27.3.19 - 22.4.19
//Vaughan Webb
//input - N/A
//prints an empty grid on a clear screen
void AGridPrint()
{
	system("cls");
	cout << "____________" << endl;
	cout << "|          |" << endl;
	cout << "|          |" << endl;
	cout << "|          |" << endl;
	cout << "|          |" << endl;
	cout << "|          |" << endl;
	cout << "|          |" << endl;
	cout << "|          |" << endl;
	cout << "|          |" << endl;
	cout << "|          |" << endl;
	cout << "|          |" << endl;
	cout << "____________" << endl;
}

//27.3.19 - 22.4.19
//Vaughan Webb
//input - the destination and current position - 2x integers
//calculates the H value which is the distance from the current postion to the destination 
//by only moving in square directions also knowen as the Manhattan method
int Hcalc(int des, int pos)
{
	//these four lines breaks the map co-ordinates back into thier x and y positions
	int desX = des % 10;
	int posX = pos % 10;
	int desY = ((des - desX) / 10);
	int posY = ((pos - posX) / 10);

	//this returns the H bos by calculating the diffrence between the x positons of both and the y positions of both (abs to keep positive)
	//then *10 becasue manhattan method then add together for the final h value
	return ((10 * (abs(desX - posX))) + (10 * (abs(desY - posY))));
}

//27.3.19 - 22.4.19
//Vaughan Webb
//input - number to find on the closed list and the closed list - 1x integer, 1x 2D vector of integers 
//find function goes through the closed list to find a position and returns the index of the position
int find(int findee, vector<vector<int>> Closed)
{
	int ans = NULL;

	for (int j = 0; j < static_cast<int>(Closed.size()); j++) //for loop that looks through the entire closed loop
	{
		//checks if the current itteration has the same position to the value we are looking for if so sets ans to it 
		if (Closed.at(j).at(0) == findee) 
		{
			ans = j; 
		}
	}
	//return ans which will either be NULL or the correct answer if it exists
	return(ans);
}

//27.3.19 - 22.4.19
//Vaughan Webb
//input - map co-ordinates - 1x integer
//little function that takes in the map co-ordinates and returns the X position 
int indexXPos(int indexX)
{
	return (indexX % 10);
}

//27.3.19 - 22.4.19
//Vaughan Webb
//input - map co-ordinates and x position of map co-ordinates - 2x integers
//little function that takes in the map co-ordinates and X position (convenianlty provided by the previous function) then returns the Y position 
int indexYPos(int indexY, int indexX)
{
	return((indexY - indexX) / 10);
}

//27.3.19 - 22.4.19
//Vaughan Webb
//input - direction and the map co-ordinates - 2x integers
//getpos gets the position of the map co-ordinates after being moves in a passed through direction 
int GetPos(int dir, int index)
{
	//breaks the current co-ordinates into X and Y positions
	int indexX = indexXPos(index);
	int indexY = indexYPos(index, indexX);

	//depending on the direction given changes x or y positions
	//direction is based on numpad so 
	if (dir < 4) // 1 = down left, 2 = down, 3 = down right
	{
		indexY += 1;
	}
	if (dir > 6) // 7 = up left, 8 = up, 9 = up right
	{
		indexY -= 1;
	}
	if (dir % 3 == 0) // 3 = down right, 6 = right, 9 = up right
	{
		indexX += 1;
	}
	if ((dir - 1) % 3 == 0)// 1 = bottom left, 4 = left, 7 = top right
	{
		indexX -= 1;
	}

	//recombines to give new map co-ordinates and returns them
	int ans = (indexY * 10) + indexX;
	return(ans);
}

//27.3.19 - 22.4.19
//Vaughan Webb
//input - destination, map co-ordinates, open list and closed list - 2x integers, 2x 2D vectors
//the main calculation function, this takes in all the important variables and add things the open and closed list and 
//makes sure every number is valid
vector<vector<int>> CheckSurrounds(int Des, int IndexBest, vector<vector<int>>Open, vector<vector<int>>&Closed)
{
	//create vector to be moved to the cloed list after checking its valid
	//the vector contains important information from the best position in the open list
	//these are the assumed numbers but a check is preformed on these to makes sure there isnt a more optimal direction to come from 
	vector<int>temp{NULL, NULL, NULL};
	temp.at(0) = Open.at(IndexBest).at(0);
	temp.at(1) = abs(10 - Open.at(IndexBest).at(4)); 
	temp.at(2) = Open.at(IndexBest).at(3);

	//initilising variables
	int Pos = Open.at(IndexBest).at(0);
	int tempBestPos1 = 0;
	int tempBestF1 = temp.at(2);
	int tempPos1 = 0;
	int tempJval1 = temp.at(1);
	int Jval1 = 0;

	//checks through every direction to see if it could come from a better location
	for (int j = 1; j < 10; j++)
	{
		bool SKIP = FALSE;
		//skips 5 direction as not moving isnt a option
		if (j == 5)
		{
			SKIP = TRUE;
		}
		//makes sure not to test if its going jumping across the worldspace
		//this tests for moving left while already on the left edge 
		if (GetPos(j, temp.at(0)) % 10 == 9)
		{
			if (j == 1 || j == 4 || j == 7)
			{
				SKIP = TRUE;
			}
		}
		//same test as above but this time is checks for moving right while already on the right edge 
		if (GetPos(j, temp.at(0)) % 10 == 0)
		{
			if (j == 3 || j == 6 || j == 9)
			{
				SKIP = TRUE;
			}
		}
		//prevents from testing moving to high up our of the worldspace
		if (GetPos(j, temp.at(0)) < 0)
		{
			SKIP = TRUE;
		}
		//prevents from testing moving to low out of the worldspace
		if (GetPos(j, temp.at(0)) > 99)
		{
			SKIP = TRUE;
		}

		//if all tests passed then proced with the next checks
		if (SKIP == FALSE)
		{
			//set varible to the location being tested
			tempPos1 = GetPos(j, temp.at(0));

			for (int k = 0; k < static_cast<int>(Closed.size()); k++)
			{
				//find the location and check its not a wall
				if (tempPos1 == Closed.at(k).at(0) && Closed.at(k).at(1) != 0)
				{
					//check if the value contained in it is better then what it origally had set 
					//or if second iteration compared to the previous best option
					if (tempBestF1 < ((Hcalc(Des, Closed.at(k).at(0))) + Jval1))
					{
						//if it is better rember variables
						tempBestF1 = Hcalc(Des, Closed.at(k).at(0)) + Jval1;
						tempBestPos1 = tempPos1;
						tempJval1 = j;

					}
				}
			}
		}
	}
	//apply changes if any occured if not this remains uneffected
	temp.at(1) = tempJval1;
	temp.at(2) = tempBestF1;

	//remove it from the open list and add it to the closed list 
	Open.at(IndexBest) = Open.back();
	Open.pop_back();
	Closed.push_back(temp);

	//function to make sure that what we pushed back has a direction from 1-9 excluding 5
	//this genrally oinly occurs on the first itteration when moving form the starting position
	bool NON0 = FALSE;
	for (int i = 1; i < 10; i++)
	{
		//skip 5 as it has to have a direction to count
		if (i == 5)
		{
			i++;
		}
		if (Closed.back().at(1) == i) 
		{
			//if the direction is 1-9 this will be called at least once
			NON0 = TRUE; 
		}
	}
	//if dirction isnt 1-9 this will be false still and remove the back of the closed vector
	if (NON0 == FALSE)
	{
		Closed.pop_back();
	}

	//this loop checks the surrouning 9 positions and check to make sure they are valid options 
	//then adds them to the closed list 
	for (int i = 1; i < 10; i++)
	{
		//5 isnt a valid direction so skip it 
		if (i == 5)
		{
			i++;
		}
		//getting the f value and the h value so i can calculate the G value form them as its not stored 
		int tempno1 = Closed.at(find(Pos, Closed)).at(2);
		int tempno2 = Hcalc(Des, Closed.at(find(Pos, Closed)).at(0));
		//initlising g 
		int g = 0;
		if (i == 2 || i == 4 || i == 6 || i == 8)
		{
			// if its moving linerarly 10 + whatever the g value is calculated to have prevoiulsly been 
			g = 10 + (tempno1 - tempno2); 
		}
		else
		{
			// if its moving diagonally 14 + whatever the g value is calculated to have prevoiulsly been 
			g = 14 + (tempno1 - tempno2);
		}

		//create a temp vector with all the values that would go in if it is valid and pushing into the open list 
		//tests happen after and it is removed from the open list if it is a invalid location or a better value exists 
		vector<int>temp{ GetPos(i, Pos), Hcalc(Des, GetPos(i, Pos)) , g , Hcalc(Des, GetPos(i, Pos)) + g, i };
		Open.push_back(temp);


		bool OutOfRange = false;
		//if the location post movement is on the left edge
		if (GetPos(i, Pos) % 10 == 0)
		{
			//but the direction is to the right
			if (i == 9 || i == 6 || i == 3)
			{
				if (OutOfRange == false)
				{
					//remove it because its corssed the worldspace
					Open.pop_back();
					//set OutOfRange to true so no following tests effect anything as its alreay removed
					OutOfRange = true;
				}

			}
		}
		//if the location post movement is on the right edge
		if (GetPos(i, Pos) % 10 == 9)
		{
			//but the direction is to the left 
			if (i == 7 || i == 4 || i == 1)
			{
				//if its still valid
				if (OutOfRange == false)
				{
					//remove it because its crossed the wordspace
					Open.pop_back();
					OutOfRange = true;
				}
			}
		}

		//if its still valid
		if (OutOfRange == false)
		{
			//if the direction that  its trying to move is on a diagonal 
			if (i == 1 || i == 3 || i == 7 || i == 9)
			{
				//initlising variables
				int UP = 0;
				int DOWN = 0;
				int LEFT = 0;
				int RIGHT = 0;
				//check up down left and right compared to the position after moving in direction i 
				UP = find(GetPos(8, (GetPos(i, Pos))), Closed);
				DOWN = find(GetPos(2, (GetPos(i, Pos))), Closed);
				LEFT = find(GetPos(4, (GetPos(i, Pos))), Closed);
				RIGHT = find(GetPos(6, (GetPos(i, Pos))), Closed);
				//if its on the closed list 
				if (UP != NULL)
				{
					//if value stored is 0 (trait the only walls have)
					if (Closed.at(UP).at(2) == 0)
					{
						//only directions 1 and 3 are effected if there is a wall in the up direction
						//rember we are testing post movement so if there is a wall above 1 or 3 it means it cut corners to get there
						if (i == 1 || i == 3)
						{
							//variable to pop later as its cut a corner to get to this position
							OutOfRange = true;
						}
					}
				}
				//if its on the closed list 
				if (DOWN != NULL)
				{
					//if value stored is 0 (trait the only walls have)
					if (Closed.at(DOWN).at(2) == 0)
					{
						//only direction 7 and 9 are affected by a wall to down from them  
						if (i == 7 || i == 9)
						{
							//variable to pop later as its cut a corner to get to this position
							OutOfRange = true;
						}
					}
				}
				//if its on the closed list 
				if (LEFT != NULL)
				{
					//if value stored is 0 (trait the only walls have)
					if (Closed.at(LEFT).at(2) == 0)
					{
						//only direction 3 and 9 are affected by a wall to their left 
						if (i == 3 || i == 9)
						{
							//variable to pop later as its cut a corner to get to this position
							OutOfRange = true;
						}
					}
				}
				//if its on the closed list 
				if (RIGHT != NULL)
				{
					//if value stored is 0 (trait the only walls have)
					if (Closed.at(RIGHT).at(2) == 0)
					{
						//only direction 1 and 7 are affected by a wall to their right 
						if (i == 1 || i == 7)
						{
							//variable to pop later as its cut a corner to get to this position
							OutOfRange = true;
						}
					}
				}
			}
			//if its cut corners then this will be called
			if (OutOfRange == true)
			{
				//remove it as cutting isnt allowed
				Open.pop_back();
			}
		}

		//checks to make sure the location is still within the worldspace and hasnt gone to far up 
		if (Open.back().at(0) < 0)
		{
			//only change if its still there
			if (OutOfRange == false)
			{
				//remove it 
				Open.pop_back();
				OutOfRange = true;
			}
		}
		//checks to make sure the location is still within the worldspace and hasnt gone to far down 
		if (Open.back().at(0) > 99)
		{
			//only change if its still there
			if (OutOfRange == false)
			{
				//remove it
				Open.pop_back();
				OutOfRange = true;
			}
		}

		//initlise varaibles
		bool Overwrite = false;
		int IOverwrite = 0;

		//makes sure its isnt already removed
		if (OutOfRange == false)
		{
			//itterate through everything on the open list
			for (int h = 1; h < static_cast<int>(Open.size()) - 1; h++)
			{
				//if the on we are trying to add is already has a position its sharing with another one on the open list
				if (Open.back().at(0) == Open.at(h).at(0))
				{
					//set to true and rember the location of the shared position
					Overwrite = true;
					IOverwrite = h;
				}
			}
			//if the new one does share a position 
			if (Overwrite == true)
			{
				//check which of the 2 have the better value
				if (Open.back().at(3) > Open.at(IOverwrite).at(3))
				{
					//if the old one is better pop the new one 
					Open.pop_back();
				}
				else
				{
					// if the new one is better swap the old and the new one and pop the old one
					Open.at(IOverwrite) = Open.back();
					Open.pop_back();
				}
			}
		}

		//if the test is still valid location
		if (OutOfRange == false && Overwrite == false)
		{
			//chack through everything on the closed list
			for (int f = 0; f < static_cast<int>(Closed.size()); f++)
			{
				//if the one we are trying to place exists on the closed list then remove it
				if (Open.back().at(0) == Closed.at(f).at(0))
				{
					Open.pop_back();
				}
			}
		}
	}
	//return the new open list after the surrounding positions have been checked
	return(Open);
}

//27.3.19 - 22.4.19
//Vaughan Webb
//input - open list - 1x 2D vector
//goes through the open list and prints all positions to the screen
void printOpen(vector<vector<int>>Open)
{
	for (int i = 1; i < static_cast<int>(Open.size()); i++)
	{
		//calculations to chnage the position to x and y values and goto the resluts position
		gotoxy(indexXPos(Open.at(i).at(0)) +2 , indexYPos(Open.at(i).at(0), indexXPos(Open.at(i).at(0))) +1);
		cout << "\bO";
	}
}

//27.3.19 - 22.4.19
//Vaughan Webb
//input - closed list - 1x 2D vector
// goes through every value on the closed list and prints a corrosponding character onto the screen
void printClosed(vector<vector<int>>Closed)
{
	for (int i = 0; i < static_cast<int>(Closed.size()); i++)
	{
		//calculations to go the the position in question
		gotoxy(indexXPos(Closed.at(i).at(0)) +2, indexYPos(Closed.at(i).at(0), indexXPos(Closed.at(i).at(0)))+1);

		if (Closed.at(i).at(1) == 0) //all walls are assigned a direction of 0 so easy to diffrienate
		{
			cout << "\bW";
		}
		else //if its non 0 it is a regular closed list memeber
		{
			cout << "\b0"; 
		}
	}

	//handy calculations to print the calue at the back of the closed list so in other words the most recent thing added to the close list or traceback
	//gotoxy(indexXPos(Closed.back().at(0)) + 2, indexYPos(Closed.back().at(0), indexXPos(Closed.back().at(0))) + 1);
	//cout << "\bC";
}

//27.3.19 - 22.4.19
//Vaughan Webb
//input - the destination and the closed list - 1x integer, 1x 2D vector
//goes to the recorded values for the starting and finishing position and prints them on the screen 
void printStartFin(int Des, vector<vector<int>>Closed)
{
	//calculations to extract the xypos from the closed list
	gotoxy(indexXPos(Closed.at(0).at(0)) +2, indexYPos(Closed.at(0).at(0), indexXPos(Closed.at(0).at(0))) + 1); 
	cout << "\bS";
	//same calculations as before but its stored as a int rather then a int in a vector in a vector so its cleaner to acess
	gotoxy(indexXPos(Des) + 2, indexYPos(Des, indexXPos(Des)) + 1); 
	cout << "\bD";
}

//27.3.19 - 22.4.19
//Vaughan Webb
//input - N/A
//the message to print when no more valid positions in the open list remain to try and place 
void noMoreSpace()
{
	gotoxy(30, 0);
	cout << "no more possible moves" << endl;
	gotoxy(30, 1);
	system("pause");
	system("CLS");
}

//27.3.19 - 22.4.19
//Vaughan Webb
//input - the destination and the closed list - 1x integer, 1x 2D vector
//function that when called follows path of closed list from destination back to start highlighting the 
//most efficent route without cornercutting
void traceBack(int Des, vector<vector<int>>Closed)
{
	//initlsing values
	int ans = 0;
	int temp = Des;
	int temp1 = 0;

	//a seprate loop before the main one as the one specfifcly handles the destination as a direction is not stored within it 
	for (int i = 1; i < 10; i++)
	{
		//the direction of not moving isnt an option
		if (i == 5) 
		{
			i++;
		}
		temp1 = GetPos(i, Des);

		//stantment to make sure it doesnt cut corners for this specific instance
		bool SKIP = false;
		if (i == 1 || i == 3 || i == 7 || i == 9) //if testing moving on a angled direction
		{
			int UP = 0;
			int DOWN = 0;
			int LEFT = 0;
			int RIGHT = 0;
			//check up down left and right compared to the position after moving in direction i 
			UP = find(GetPos(8, (GetPos(i, Des))), Closed);
			DOWN = find(GetPos(2, (GetPos(i, Des))), Closed);
			LEFT = find(GetPos(4, (GetPos(i, Des))), Closed);
			RIGHT = find(GetPos(6, (GetPos(i, Des))), Closed);

			//if its on the closed list
			if (UP != NULL)
			{
				//if value stored is 0 (trait the only walls have)
				if (Closed.at(UP).at(2) == 0)
				{
					//only directions 1 and 3 are effected if there is a wall in the up direction
					//rember we are testing post movement so if there is a wall above 1 or 3 it means it cut corners to get there
					if (i == 1 || i == 3)
					{
						//skip becomes true meaning that the tested direction cannot be used 
						SKIP = true;										
					}
				}
			}
			//if its on the closed list 
			if (DOWN != NULL)
			{
				//if value stored is 0 (trait the only walls have)
				if (Closed.at(DOWN).at(2) == 0)
				{
					//only direction 7 and 9 are effected by a down wall
					if (i == 7 || i == 9)
					{
						//skip as this direction is invalid to test 
						SKIP = true;
					}
				}
			}
			//if its on the closed list 
			if (LEFT != NULL)
			{
				//if value stored is 0 (trait the only walls have)
				if (Closed.at(LEFT).at(2) == 0)
				{
					//only direction 3 and 9 are affected by a wall to their left 
					if (i == 3 || i == 9)
					{
						//skip as this direction is invalid to test 
						SKIP = true;
					}
				}
			}
			//if its on the closed list 
			if (RIGHT != NULL)
			{
				//if value stored is 0 (trait the only walls have)
				if (Closed.at(RIGHT).at(2) == 0)
				{
					//only direction 1 and 7 are effected by a wall on their right
					if (i == 1 || i == 7)
					{
						//skip as this direction is invalid to test 
						SKIP = true;
					}
				}
			}
		}

		//if skip remains (valid to test )
		if (SKIP == false)
		{
			//find the value we are testing on the closed list and make sure its not a wall
			for (int j = 0; j < static_cast<int>(Closed.size()) - 1; j++)
			{
				if (Closed.at(j).at(0) == temp1 && Closed.at(j).at(1) != 0)
				{
					//if conditions are met change set the answer to the chosen direction
					ans = i;
				}
			}
		}
	}

	//loop for the rest of the values now that we have our starting direction
	while (true)
	{
		//move to the direction of ans which will be the direction we got from the above function or refound in the loop 
		//if its not the first itteration
		temp = GetPos(ans, temp);
		gotoxy(indexXPos(temp) + 2, indexYPos(temp, indexXPos(temp)) + 1);
		//find the direction inside the node we just moved to and set the to answer for the next itteration 
 		ans = Closed.at(find(temp, Closed)).at(1);
		//draws the traceback using a "-" symbol for readability 
		cout << "\b-";

		//the break condition is reaching the starting position which holds a direction of 5 which is unique to it 
		if (ans == 5) 
		{
			//print and inform the user that the traceback line has beef found
			cout << "\bS";
			gotoxy(15, 0);
			cout << "we made it woo" << endl;
			gotoxy(15, 1);
			system("pause");
			//line of breaks will return to the menu from here
			break;
		}

	}
}

//27.3.19 - 22.4.19
//Vaughan Webb
//input - the destination, starting position and the closed list - 2x integers, 1x 2D vector 
//a* setup is done next this function calls the functions to find the next best spot on the open list 
//mvoe there and when its does trace back to the start, or if unable to says so and exits out
void Acalculate(int Des, int Pos, vector<vector<int>> Closed)
{
	//values for initilising the open vector
	int x = 1;
	int y = 5;
	vector<vector<int>>Open(x, vector<int>(y, 999)); //initlise
	//stating pos to the open list
	vector<int>temp{ Pos, Hcalc(Des, Pos) , NULL ,NULL, NULL};
	Open.push_back(temp);
	//moves it to 0th position infront of walls 
	//starting pos to the closed list 
	vector<int>vTemp {Pos, 5, Hcalc(Des, Pos)};
	Closed.push_back(vTemp);
	vTemp = Closed.at(0);
	Closed.at(0) = Closed.back();
	Closed.back() = vTemp;

	//check the surrounds from the starting position
	int IndexBest = 0;
	Open = CheckSurrounds(Des, 1, Open, Closed);

	//loop that picks the lowest position in the openlist and then checks surrounds around that position and moves it to the closed list 
	//also calls when there are no more spaces avalible to move and calls traceback when the destination has been found
	while (true)
	{
		int i1 = 1000;
		int cBest = 1000;
		//runs through everything in the open list looking for the one with the lowest value to test next 
		for (int i = 1; i < static_cast<int>(Open.size()); i++)
		{
			int test = Open.at(i).at(3);
			gotoxy(indexXPos(Open.at(i).at(0)) + 1, indexYPos(Open.at(i).at(0), indexXPos(Open.at(i).at(0))) + 1);
			if (test < cBest) // if lower the the prevously tested option 
			{
				i1 = i;
				cBest = test;
			}
		}
		IndexBest = i1;

		//is the open list has no testable values left in it 
		if (Open.size() == 1)
		{
			//no moves function
			noMoreSpace();
			break;
		}
		//if the best value is the ame as the destination, which means its won
		if (Open.at(IndexBest).at(1) == 0)
		{
			//trace best path function
			//adds destination to closed list
			vTemp.at(0) = Des;
			vTemp.at(1) = 0;
			vTemp.at(2) = 0;
			Closed.push_back(vTemp);

			//calls traceback 
			traceBack(Des, Closed);
			//breaks when thats done so it can return to the main 
			break;
		}

		//if it hasnt won or lost do a regular search the surroundsing of the best spot on the open list
		Open = CheckSurrounds(Des, IndexBest, Open, Closed);

		//clars screen, print a clean grid, prints the open list, prints the closed list then prints the starting and finshing positions
		AGridPrint();
		printOpen(Open);
		printClosed(Closed);
		printStartFin(Des, Closed);
	}
}

//27.3.19 - 22.4.19
//Vaughan Webb
//input - type to execute - 1x integer
//pritns various things depending on what the user is currently placing 
void typeprint(int type)
{
	if (type == 0) //fist itteration the destination is being placed
	{
		cout << "you are currently placing destination";
	}
	if (type == 1)//second itteration source is being placed
	{
		cout << "you are currently placing      source";
	}
	if (type == 2) // thried itteration walls are being placed
	{
		cout << "you are currently placing        wall";
	}
}

//27.3.19 - 22.4.19
//Vaughan Webb
//input - type to execute, the starting and finishing position how many walls are to be places and the closed list
//4x integers, 1x 2D vector
//the placement function for the starting, finishing and all the wall positions
int placement(int type, int Des, int Pos, int WallCount, vector<vector<int>> Closed)
{
	//initilising variables
	int x = 0;
	int y = 0;
	int xMax = 1;
	int yMax = 1;
	int ch = 0;
	int ans = 0;


	while (ch != 13) //while enter isnt pressed
	{
		if (WallCount == 0)
		{
			break;
		}
		gotoxy(0, 15);
		cout << "WASD or wasd to move and enter to place" << endl; //instructions
		typeprint(type); //tells user what they are currently placing
		cout << endl;
		cout << "x: " << x << endl << "y: " << y << endl; //prints the current co-ordinates of the mouse 
		gotoxy(x + 1, y + 1);
		ch = _getch();
		if (ch == 119 || ch == 87) //w key pressed
		{
			if (yMax > 1) //checks it can move then does so and adjust values accordingly
			{
				y -= 1;
				yMax -= 1;
			}

		}
		else if (ch == 97 || ch == 65) //a key pressed
		{
			if (xMax > 1) //checks it can move then does so and adjust values accordingly
			{
				x -= 1;
				xMax -= 1;
			}
		}
		else if (ch == 115 || ch == 83) //s key pressed
		{
			if (yMax < 10) //checks it can move then does so and adjust values accordingly
			{
				y += 1;
				yMax += 1;
			}
		}
		else if (ch == 100 || ch == 68) //d key pressed
		{
			if (xMax < 10) //checks it can move then does so and adjust values accordingly
			{
				x += 1;				
				xMax += 1;
			}
		}
		else if (ch == 13) //enter key pressed
		{
			ans = (y * 10) + x; //convers the xy position to a number between 0-100 that will represent its position on the grid
			if (type == 2)
			{
				for (int i = 0; i < static_cast<int>(Closed.size()); i++) //goes through everything on the closed list and makes sure that walls cant be placed on other walls
				{
					if (ans == Closed.at(i).at(0))
					{
						ans = Des; //fail condition that doesnt effect anything else
					}
				}
			}


			if (type == 0)  //place the destination
			{
				cout << " \bD" << endl;
			}
			else if (type == 1 && ans != Des) //is placing source and it doesnt shar position with the destination
			{
				cout << " \bS" << endl;
			}
			else if (type == 2 && ans != Des && ans != Pos) //is placing walls and its not placing ontop of destination or position 
			{
				cout << " \bW" << endl;
				WallCount -= 1;
				if (WallCount > 0) //makes sure the correct ammount of wall are placed
				{
					ch = NULL; //not run if the last wall has been placed so ch stays as 13 and it breaks
				}
				//pushes the walls position into the closed vector
				vector<int> vAns{ ans, NULL, NULL }; 
				Closed.push_back(vAns);
			}
			else //any other key is pressed
			{
				ch = NULL;
			}
		}
	}
	//if the last time the function is called
	if (type == 2)
	{
		Acalculate(Des, Pos, Closed);	//move onto the next stage
	}
	return (ans);
}

//27.3.19 - 22.4.19
//Vaughan Webb
//input - N/A
//gets the a* search started calls placemnet functions and initilises values
void AStarSetup()
{
	//initilising vectors and various positions
	vector<vector<int>> closed;
	int WallNo = 5;
	int Destination = 0;
	int StartingPos = 0;


	//fun way to let the user choose the ammount of walls they want to place between the chosen values
	cout << "how many walls you you like to place? (10 X 10 Grid)" << endl;
	cout << "between 0 and 98" << endl;
	char ch = 0;
	//modular if i need to change the location
	int Xprint = 15;
	int Yprint = 10;
	//instructions
	gotoxy(Xprint - 1, Yprint - 1);
	cout << "w = +1";
	gotoxy(Xprint - 8, Yprint);
	cout << "a = -10";
	gotoxy(Xprint - 1, Yprint + 1);
	cout << "s = -1";
	gotoxy(Xprint + 5, Yprint);
	cout << "d = +10";
	//while enter isnt pressed
	while (ch != 13)
	{
		//clear old value and rewrite with new 
		gotoxy(Xprint + 4, Yprint);
		cout << "\b\b\b\b    ";
		gotoxy(Xprint, Yprint);
		cout << "(" << WallNo << ")";
		gotoxy(Xprint, Yprint);
		Sleep(40); //small sleep so it isnt so sensitive
		ch = _getch();

		if (ch == 119 || ch == 87)//w key pressed +1
		{
			if (WallNo < 98) //smaller then 98 it can +1
			{
				WallNo++;
			}
		}
		else if (ch == 115 || ch == 83) //s key pressed -1
		{
			if (WallNo > 0) //larger then 0 it can -1
			{
				WallNo--;
			}
		}
		else if (ch == 97 || ch == 65) //s key pressed -10
		{
			if (WallNo > 0) //larger then 0 it can -10
			{
				if (WallNo < 10) //unless its less then 10 then it sets it to 0
				{
					WallNo = 0;
				}
				else
				{
					WallNo -= 10;
				}
			}
		}
		else if (ch == 100 || ch == 68) //s key pressed +10
		{
			if (WallNo < 98) //smaller then 98 it can +10
			{
				if (WallNo > 88)//unless its less greater 88 then it sets it to 98
				{
					WallNo = 98;
				}
				else
				{
					WallNo += 10;
				}
			}
		}
	}

	//clears the screen and prints a grid to place on 
	AGridPrint();

	//first value determins how it acts amd what its placing within the same placment function
	//0 == destination
	//1 == source(starting)
	//2 == obstacle
	
	Destination = placement(0, NULL, NULL, 1, closed); 
	StartingPos = placement(1, Destination, NULL, 1, closed);
				  placement(2, Destination, StartingPos, WallNo, closed); //the next part of the function is called after the walls are placed

}

#pragma endregion

#pragma region "menus / main"

//27.3.19 - 22.4.19
//Vaughan Webb
//input - N/A
//prints the menu text to the console and takes their input 
//stores their option as a char to later convert to ascii value
int menu()
{
	char opt; 
	cout << "A S T A R  &  H I L L  C L I M B" << endl;
	cout << "1) A*" << endl;
	cout << "2) hillclimb" << endl;
	cout << "3) exit" << endl;

	cin >> opt;
	return (opt);
}

//27.3.19 - 24.4.19
//Vaughan Webb
//input - N/A
//prints the menu text to the console and takes their input 
//stores their option as a char to later convert to ascii value
int menu2()
{
	char opt;
	system("cls");
	cout << "which method to solve the N queens problem" << endl;
	cout << "1) Hillclimbing" << endl;
	cout << "2) Simulated Annealing" << endl;

	cin >> opt;
	return (opt);
}

//27.3.19 - 24.4.19
//Vaughan Webb
//input - N/A
//prints the menu text to the console and takes their input 
//stores their option as a int to later make sure is larger then 3
int menu3()
{
	int opt;
	system("cls");
	cout << "How many Queens would you like" << endl;
	cout << "must be > 3 " << endl;

	cin >> opt;
	return (opt);
}

//27.3.19 - 22.4.19
//Vaughan Webb
//input - N/A
//start of the program, creates a loop around the menu 
int main()
{
	//initilises opt to a int 
	int opt;
	//seed for random number generator
	srand(time(NULL));
	while (true)
	{
		system("CLS");
		//menu returns a char of either 1, 2 or 3 and we conver it to ascii 
		opt = menu();
		if (opt == 49) //option 1
		{
			//start doing a*
			AStarSetup();
		}
		else if (opt == 50) // option 2
		{
			//resets opt to be used again
			opt = NULL;
			//loops untill opt == either 49 or 50 (1 or 2)
			while (opt != 49 && opt !=50)
			{
				opt = menu2();
			}
			//if the hillclim option is choesn
			if (opt == 49)
			{
				//reset opt for resuing
				opt = NULL;
				//loops untill an option greater then 3 is chosen
				while (opt < 4)
				{
					opt = menu3();
				}
				//beigns the setup of hillclimb using opt as number of queens
				HillClimbSetup(opt);
				opt = NULL;

			}
			else if (opt == 50)
			{
				opt = NULL;
				//loops untill an option greater then 3 is chosen
				while (opt < 4)
				{
					opt = menu3();
				}
				AnnealSetup(opt);
				opt = NULL;


			}
		}
		else if (opt == 51) // option 3
		{
			//quits
			return(0);
		}
		else
		{
			//invalid
			opt = NULL;
		}


	}

	return(0);
}
#pragma endregion