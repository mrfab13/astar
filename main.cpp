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
	int max = 10;
	int tempi = 1;
	int Pos = Open.at(IndexBest).at(0);

	vector<int>temp{NULL, NULL, NULL};
	temp.at(0) = Open.at(IndexBest).at(0);
	temp.at(1) = Open.at(IndexBest).at(4); 
	temp.at(2) = Open.at(IndexBest).at(3);
	Open.at(IndexBest) = Open.back();
	Open.pop_back();

	//for (int i = 0; i < static_cast<int>(Open.size()); i++)
	//{
	//	if (temp.at(0) == Open.at(i).at(0))
	//	{
	//		if (temp.at(2) > Open.at(i).at(3))
	//		{
	//			//swap
	//			temp.at(1) = Open.at(i).at(4);
	//			temp.at(2) = Open.at(i).at(3);
	//		}
	//	}
	//}

	Closed.push_back(temp);




	for (int i = 1; i < max; i++)
	{



		int g = 0;
		if (tempi == 2 || tempi == 4 || tempi == 6 || tempi == 8)
		{
			g = 10;
		}
		else
		{
			g = 14;
		}
		


		vector<int>temp{ GetPos(tempi, Pos), Hcalc(Des, GetPos(tempi, Pos)) , g , Hcalc(Des, GetPos(tempi, Pos)) + g, tempi };

	//	if ()  TODO keppeind better DIR
		for (int i = 0; i < static_cast<int>(Closed.size()); i++)
		{
			if (temp.at(0) == Closed.at(i).at(0))
			{
				if (temp.at(3) > Closed.at(i).at(2))
				{
					temp.at(4) = Closed.at(i).at(1);
					temp.at(3) = Closed.at(i).at(2);
				}
			}

		}

		Open.push_back(temp);
		//gotoxy(indexXPos(GetPos(tempi, Pos))+1, indexYPos(GetPos(tempi, Pos), indexXPos(GetPos(tempi, Pos)))+1);
		//cout << " \b0";

		bool Overwrite = false;
		int IOverwrite = 0;
		for (int h = 1; h < static_cast<int>(Open.size())-1; h++)
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
			i--;
			max--;

		}

		bool isntClosed = true;
		for (int f = 0; f < static_cast<int>(Closed.size()); f++)
		{
			if (Open.back().at(0) == Closed.at(f).at(0))
			{
				isntClosed = false;
				if (Open.back().at(3) < Closed.at(f).at(2))
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
			i--;
			max--;
		}

		bool OutOfRange = false;
		if (Pos % 10 == 0)
		{
			if (tempi == 1 || tempi == 4 || tempi == 7)
			{
				if (isntClosed == true && Overwrite == false && OutOfRange == false)
				{
					Open.pop_back();
					i--;
					max--;
					OutOfRange = true;
				}

			}
		}
		if (Pos % 10 == 9)
		{
			if (tempi == 3 || tempi == 6 || tempi == 9)
			{
				if (isntClosed == true && Overwrite == false && OutOfRange == false)
				{
					Open.pop_back();
					i--;
					max--;
					OutOfRange = true;
				}
			}
		}


		if (Open.back().at(0) < 0)
		{
			if (isntClosed == true && Overwrite == false && OutOfRange == false)
			{
				Open.pop_back();
				i--;
				max--;
				OutOfRange = true;
			}
		}
		if (Open.back().at(0) > 99)
		{
			if (isntClosed == true && Overwrite == false && OutOfRange == false)
			{
				Open.pop_back();
				i--;
				max--;
				OutOfRange = true;
			}
		}

		tempi++;

	}
	return(Open);
}

void printOpen(vector<vector<int>>Open)
{
	for (int i = 1; i < static_cast<int>(Open.size()); i++)
	{
		gotoxy(indexXPos(Open.at(i).at(0)) +2 , indexYPos(Open.at(i).at(0), indexXPos(Open.at(i).at(0))) +1);
		cout << "\b0";

	}
}

void printClosed(vector<vector<int>>Closed)
{
	for (int i = 0; i < static_cast<int>(Closed.size()); i++)
	{
		gotoxy(indexXPos(Closed.at(i).at(0)) +2, indexYPos(Closed.at(i).at(0), indexXPos(Closed.at(i).at(0)))+1);

		if (Closed.at(i).at(1) == 0)
		{
			cout << "\bF";
		}
		else
		{
			cout << "\bW";
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
	system("CLS");
	gotoxy(0, 0);
	cout << "no more possible moves" << endl;
	system("pause");
	system("CLS");

	cout << "time and space have become meaningless" << endl;
	system("pause");
	system("CLS");

	cout << "infinite search contained in a finite space" << endl;
	system("pause");
	system("CLS");

	cout << "infinite time, results unchanged" << endl;
	system("pause");
	system("CLS");

	cout << "Did I even Exist?" << endl;
	system("pause");
	system("CLS");

	cout << "endl; my life" << endl;
	system("pause");
	system("CLS");

	cout << "please" << endl;
	system("pause");
	system("CLS");

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

void traceBack(int Des, vector<vector<int>>Closed)
{
	int ans = 0;
	int temp = Des;
	int temp1 = 0;
	bool test = false;

	for (int i = 1; i < 10; i++)
	{
		for (int j = 0; j < static_cast<int>(Closed.size()) - 1; j++)
		{
			temp1 = GetPos(i, Des);
			if (Closed.at(j).at(0) == temp1)
			{
				ans = j;
				test = true;
			}
		}
		if (test == true)
		{
			if (Closed.at(ans).at(1) != 0)//is this line redundant?
			{
				ans = Closed.at(ans).at(1);
			}
		}
		test = false;

	}

	temp = Des;

	while (true)
	{

		for (int i = 1; i < 10; i++)
		{
			if (i == ans)
			{
				i = abs(10 - i);
				temp = GetPos(i, temp);
				ans = Closed.at(find(temp, Closed)).at(1);

				gotoxy(indexXPos(temp)+2, indexYPos(temp, indexXPos(temp) )+1);
				cout << "\bV";
				i = 11;

			}

		}
		if (ans == 0)
		{
			system("CLS");
			cout << "we made it woo" << endl;
			cout << "although since its degug still its probably not workign :p" << endl;
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
	vector<int>vTemp {Pos, NULL, NULL};
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


void typeprint(int type)
{
	if (type == 0)
	{
		cout << "you are currently placing destination";
	}
	if (type == 1)
	{
		cout << "you are currently placing      source";
	}
	if (type == 2)
	{
		cout << "you are currently placing        wall";
	}
}

int placement(int type, int Des, int Pos, int WallCount, vector<vector<int>> Closed)
{

	int x = 0;
	int y = 0;
	int xMax = 1;
	int yMax = 1;

	int ch = 0;
	int ans = 0;


	while (ch != 13)
	{
		gotoxy(0, 15);
		cout << "WASD or wasd to move and enter to place" << endl;
		typeprint(type);
		cout << endl;
		cout << "x: " << x << endl << "y: " << y << endl;
		gotoxy(x + 1, y + 1);
		ch = _getch();
		if (ch == 119 || ch == 87) //w key pressed
		{
			if (yMax > 1)
			{
				y -= 1;
				yMax -= 1;
			}

		}
		else if (ch == 97 || ch == 65) //a key pressed
		{
			if (xMax > 1)
			{
				x -= 1;
				xMax -= 1;
			}
		}
		else if (ch == 115 || ch == 83) //s key pressed
		{
			if (yMax < 10)
			{
				y += 1;
				yMax += 1;
			}
		}
		else if (ch == 100 || ch == 68) //d key pressed
		{
			if (xMax < 10)
			{
				x += 1;				
				xMax += 1;
			}
		}
		else if (ch == 13) //enter key pressed
		{
			ans = (y * 10) + x;
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
	if (type == 2)
	{
		Acalculate(Des, Pos, Closed);
	}
	return (ans);
}

void AStarSetup()
{
	vector<vector<int>> closed;
	int WallNo = 0;
	int Destination = 0;
	int StartingPos = 0;

	cout << "how many walls you you like to place? (10 X 10 Grid)" << endl;
	cin >> WallNo;
	AGridPrint();


	//0 == destination
	//1 == source(starting)
	//2 == obstacle
	Destination = placement(0, NULL, NULL, NULL, closed);
	StartingPos = placement(1, Destination, NULL, NULL, closed);
	placement(2, Destination, StartingPos, WallNo, closed);

}

int menu()
{
	char opt;
	cout << "A * & H I L L C L I M B" << endl;
	cout << "1) A*" << endl;
	cout << "2) hillclimb" << endl;
	cout << "3) exit" << endl;
	cin >> opt;
	return (opt);
}



int main()
{
	int opt;
	while (true)
	{
		system("CLS");
		opt = menu();
		if (opt == 49)
		{
			AStarSetup();
		}
		else if (opt == 50)
		{
			HillClimbSetup();
		}
		else if (opt == 51)
		{
			return(0);
		}
		else
		{
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