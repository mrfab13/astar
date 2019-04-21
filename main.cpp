#include <iostream>
#include <ctime>
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <conio.h>
#include <array>
#include <vector>

using namespace std;

void gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void HillClimbSetup()
{
	cout << "WIP" << endl;
	system("pause");
}



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

int Hcalc(int des, int pos)
{
	int desX = des % 10;
	int posX = pos % 10;
	int desY = ((des - desX) / 10);
	int posY = ((pos - posX) / 10);
	return ((10 * (abs(desX - posX))) + (10 * (abs(desY - posY))));
}

int find(int findee, vector<vector<int>> Closed)
{
	int ans = NULL;

	for (int j = 0; j < static_cast<int>(Closed.size()); j++)
	{
		if (Closed.at(j).at(0) == findee)
		{
			ans = j;
		}
	}

	return(ans);
}

int indexXPos(int indexX)
{
	return (indexX % 10);
}
int indexYPos(int indexY, int indexX)
{
	return((indexY - indexX) / 10);
}

int GetPos(int dir, int index)
{
	int indexX = indexXPos(index);
	int indexY = indexYPos(index, indexX);
	if (dir < 4)
	{
		indexY += 1;
	}
	if (dir > 6)
	{
		indexY -= 1;
	}
	if (dir % 3 == 0)
	{
		indexX += 1;
	}
	if ((dir - 1) % 3 == 0)
	{
		indexX -= 1;

	}

	int ans = (indexY * 10) + indexX;
	//gotoxy(indexX+2, indexY+1);
	//cout << "\b0";
	return(ans);
}

vector<vector<int>> CheckSurrounds(int Des, int IndexBest, vector<vector<int>>Open, vector<vector<int>>&Closed)
{
	int Pos = Open.at(IndexBest).at(0);

	vector<int>temp{NULL, NULL, NULL};
	temp.at(0) = Open.at(IndexBest).at(0);
	temp.at(1) = abs(10 - Open.at(IndexBest).at(4)); 
	temp.at(2) = Open.at(IndexBest).at(3);
	if (temp.at(0) == 49)
	{
		cout << "HI";
	}


	int tempBestPos1 = 0;
	int tempBestF1 = temp.at(2);
	int tempPos1 = 0;
	int tempJval1 = temp.at(1);
	int Jval1 = 0;

	for (int j = 1; j < 10; j++)
	{
		bool SKIP = FALSE;
		if (j == 5)
		{
			SKIP = TRUE;
		}
		if (GetPos(j, temp.at(0)) % 10 == 9)
		{
			if (j == 1 || j == 4 || j == 7)
			{
				SKIP = TRUE;
			}
		}
		if (GetPos(j, temp.at(0)) % 10 == 0)
		{
			if (j == 3 || j == 6 || j == 9)
			{
				SKIP = TRUE;
			}
		}
		if (GetPos(j, temp.at(0)) < 0)
		{
			SKIP = TRUE;
		}
		if (GetPos(j, temp.at(0)) > 99)
		{
			SKIP = TRUE;
		}


		if (SKIP == FALSE)
		{
			tempPos1 = GetPos(j, temp.at(0));
			

			for (int k = 0; k < static_cast<int>(Closed.size()); k++)
			{
				if (tempPos1 == Closed.at(k).at(0) && Closed.at(k).at(1) != 0)
				{
					if (tempBestF1 < ((Hcalc(Des, Closed.at(k).at(0))) + Jval1))
					{
						tempBestF1 = Hcalc(Des, Closed.at(k).at(0)) + Jval1;
						tempBestPos1 = tempPos1;
						tempJval1 = j;

					}
				}
			}
		}
		

	}
	temp.at(1) = tempJval1;
	temp.at(2) = tempBestF1;


	Open.at(IndexBest) = Open.back();
	Open.pop_back();

	Closed.push_back(temp);

	bool NON0 = FALSE;
	for (int i = 1; i < 10; i++)
	{
		if (i == 5)
		{
			i++;
		}
		if (Closed.back().at(1) == i)
		{
			NON0 = TRUE;
		}
	}
	if (NON0 == FALSE)
	{
		Closed.pop_back();
	}




	for (int i = 1; i < 10; i++)
	{

		if (i == 5)
		{
			i++;
		}

		int tempno1 = Closed.at(find(Pos, Closed)).at(2);
		int tempno2 = Hcalc(Des, Closed.at(find(Pos, Closed)).at(0));
		int g = 0;
		if (i == 2 || i == 4 || i == 6 || i == 8)
		{
			g = 10 + (tempno1 - tempno2);
		}
		else
		{
			g = 14 + (tempno1 - tempno2);
		}

		vector<int>temp{ GetPos(i, Pos), Hcalc(Des, GetPos(i, Pos)) , g , Hcalc(Des, GetPos(i, Pos)) + g, i };

		Open.push_back(temp);


		bool OutOfRange = false;
		if (GetPos(i, Pos) % 10 == 0)
		{
			if (i == 9 || i == 6 || i == 3)
			{
				if (OutOfRange == false)
				{
					Open.pop_back();
					OutOfRange = true;
				}

			}
		}
		if (GetPos(i, Pos) % 10 == 9)
		{
			if (i == 7 || i == 4 || i == 1)
			{
				if (OutOfRange == false)
				{
					Open.pop_back();
					OutOfRange = true;
				}
			}
		}


		if (Open.back().at(0) < 0)
		{
			if (OutOfRange == false)
			{
				Open.pop_back();
				OutOfRange = true;
			}
		}
		if (Open.back().at(0) > 99)
		{
			if (OutOfRange == false)
			{
				Open.pop_back();

				OutOfRange = true;
			}
		}

		bool Overwrite = false;
		int IOverwrite = 0;
		if (OutOfRange == false)
		{
			for (int h = 1; h < static_cast<int>(Open.size()) - 1; h++)
			{
				if (Open.back().at(0) == Open.at(h).at(0))
				{
					Overwrite = true;
					IOverwrite = h;
				}
			}
			if (Overwrite == true)
			{
				if (Open.back().at(3) > Open.at(IOverwrite).at(3))
				{
					Open.pop_back();
				}
				else
				{
					Open.at(IOverwrite) = Open.back();
					Open.pop_back();
				}

		}

		}

		bool isntClosed = true;
		if (OutOfRange == false && Overwrite == false)
		{
			for (int f = 0; f < static_cast<int>(Closed.size()); f++)
			{
				if (Open.back().at(0) == Closed.at(f).at(0))
				{
					isntClosed = false;
					if (Open.back().at(3) < Closed.at(f).at(2)) //TODO remove?
					{
						if (Closed.at(f).at(2) != 0)
						{
							Closed.at(f).at(1) = Open.back().at(4);
							Closed.at(f).at(2) = Open.back().at(3);
						}
					}
				}
			}
			if (isntClosed == false)
			{
				Open.pop_back();

			}
		}



	}
	return(Open);
}

void printOpen(vector<vector<int>>Open)
{
	for (int i = 1; i < static_cast<int>(Open.size()); i++)
	{
		gotoxy(indexXPos(Open.at(i).at(0)) +2 , indexYPos(Open.at(i).at(0), indexXPos(Open.at(i).at(0))) +1);
		cout << "\bO";

	}
}

void printClosed(vector<vector<int>>Closed)
{
	for (int i = 0; i < static_cast<int>(Closed.size()); i++)
	{
		gotoxy(indexXPos(Closed.at(i).at(0)) +2, indexYPos(Closed.at(i).at(0), indexXPos(Closed.at(i).at(0)))+1);

		if (Closed.at(i).at(1) == 0)
		{
			cout << "\bW";
		}
		else
		{
			cout << "\b0";
		}
	}
	gotoxy(indexXPos(Closed.back().at(0)) + 2, indexYPos(Closed.back().at(0), indexXPos(Closed.back().at(0))) + 1);
	cout << "\bJ";

}

void printStartFin(int Des, vector<vector<int>>Closed)
{
	gotoxy(indexXPos(Closed.at(0).at(0)) +2, indexYPos(Closed.at(0).at(0), indexXPos(Closed.at(0).at(0))) + 1);
	cout << "\bS";
	gotoxy(indexXPos(Des) + 2, indexYPos(Des, indexXPos(Des)) + 1);
	cout << "\bD";

}

void noMoreSpace()
{
	gotoxy(30, 0);
	cout << "no more possible moves" << endl;
	gotoxy(30, 1);
	system("pause");
	system("CLS");

	//cout << "time and space have become meaningless" << endl;
	//system("pause");
	//system("CLS");

	//cout << "infinite search contained in a finite space" << endl;
	//system("pause");
	//system("CLS");

	//cout << "infinite time, results unchanged" << endl;
	//system("pause");
	//system("CLS");

	//cout << "Did I even Exist?" << endl;
	//system("pause");
	//system("CLS");

	//cout << "endl; my life" << endl;
	//system("pause");
	//system("CLS");

	//cout << "please" << endl;
	//system("pause");
	//system("CLS");

}

void traceBack(int Des, vector<vector<int>>Closed)
{
	int ans = 0;
	int temp = Des;
	int temp1 = 0;
	bool test = false;

	for (int i = 1; i < 10; i++)
	{
		if (i == 5)
		{
			i++;
		}
		temp1 = GetPos(i, Des);
		for (int j = 0; j < static_cast<int>(Closed.size()) - 1; j++)
		{
			if (Closed.at(j).at(0) == temp1)
			{
				ans = j;
				test = true;
			}
		}
		if (test == true)
		{
			if (Closed.at(ans).at(1) != 0)
			{
				ans = Closed.at(ans).at(1);

			}
		}
		test = false;

	}


	while (true)
	{
		temp = GetPos(ans, temp);
		gotoxy(indexXPos(temp) + 2, indexYPos(temp, indexXPos(temp)) + 1);
 		ans = Closed.at(find(temp, Closed)).at(1);
		cout << "\bV";

		if (ans == 5)
		{
			cout << "\bS";
			gotoxy(15, 0);
			cout << "we made it woo" << endl;
			gotoxy(15, 1);
			cout << "although since its degug still its probably not workign :p" << endl;
			gotoxy(15, 2);
			system("pause");
			break;
		}

	}
}

void Acalculate(int Des, int Pos, vector<vector<int>> Closed)
{
	int x = 1;
	int y = 5;

	vector<vector<int>>Open(x, vector<int>(y, 999)); //initlise
	//stating pos 
	vector<int>temp{ Pos, Hcalc(Des, Pos) , NULL ,NULL, NULL};
	Open.push_back(temp);
	//moves it to 0th position infront of walls 
	vector<int>vTemp {Pos, 5, Hcalc(Des, Pos)}; //TODO
	Closed.push_back(vTemp);
	vTemp = Closed.at(0);
	Closed.at(0) = Closed.back();
	Closed.back() = vTemp;





	int IndexBest = 0;

	Open = CheckSurrounds(Des, 1, Open, Closed);
	while (true)
	{
		int i1 = 1000;
		int cBest = 1000;
		for (int i = 1; i < static_cast<int>(Open.size()); i++)
		{
			int test = Open.at(i).at(3);
			gotoxy(indexXPos(Open.at(i).at(0)) + 1, indexYPos(Open.at(i).at(0), indexXPos(Open.at(i).at(0))) + 1);
			if (test < cBest)
			{
				i1 = i;
				cBest = test;
			}
		}
		IndexBest = i1;

		if (Open.size() == 1)
		{
			//no moves function
			noMoreSpace();
			break;
		}
		if (Open.at(IndexBest).at(1) == 0)
		{
			//trace best path function
			// des to closed list
			vTemp.at(0) = Des;
			vTemp.at(1) = 0;
			vTemp.at(2) = 0;

			Closed.push_back(vTemp);

			traceBack(Des, Closed);
			break;
		}


		Open = CheckSurrounds(Des, IndexBest, Open, Closed);

		AGridPrint();
		printOpen(Open);
		printClosed(Closed);
		printStartFin(Des, Closed);



	}


}

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
				for (int i = 0; i < static_cast<int>(Closed.size()); i++)
				{
					if (ans == Closed.at(i).at(0))
					{
						ans = Des; //fail condition that doesnt effect anything else
					}
				}
			}


			if (type == 0)
			{
				cout << " \bD" << endl;
			}
			else if (type == 1 && ans != Des)
			{
				cout << " \bS" << endl;
			}
			else if (type == 2 && ans != Des && ans != Pos)
			{
				cout << " \bW" << endl;
				WallCount -= 1;
				if (WallCount > 0)
				{
					ch = NULL;
				}
				vector<int> vAns{ ans, NULL, NULL };
				Closed.push_back(vAns);
			}
			else
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
	Destination = placement(0, NULL, NULL, NULL, closed);
	StartingPos = placement(1, Destination, NULL, NULL, closed);
	placement(2, Destination, StartingPos, WallNo, closed); //the next part of the function is called after the walls are placed

}


//prints the menu text to the console
// stores their option as a char to later convert to ascii value
int menu()
{
	char opt; 
	cout << "A * & H I L L C L I M B" << endl;
	cout << "1) A*" << endl;
	cout << "2) hillclimb" << endl;
	cout << "3) exit" << endl;

	std::cin >> opt;
	return (opt);
}


//start of the program, creates a loop around the menu 
int main()
{
	//initilises opt to a int 
	int opt;
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
			HillClimbSetup();
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

	//dont touch 
	if (false)
	{
		while (false)
		{
			break;
			break;
		}
	}
	else if (true)
	{
	}
}