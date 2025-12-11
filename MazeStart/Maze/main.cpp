/*
	GPF Week 6 - Maze Start Code
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <stdio.h>

#include "Framework.h"
using namespace std;

// Screen dimensions
int gScreenWidth{ 800 };
int gScreenHeight{ 600 };

// Delay to slow things down
int gTimeDelayMS{ 100 };

// Maze size as constants
constexpr int kMazeColumnsX{ 20 };
constexpr int kMazeRowsY{ 20 };
constexpr int viewDistance{ 4 };
constexpr int VisibleDist{ 1 + viewDistance * 2 };

/*
	2 Dimensional Arrays
	You can think of these as being an array of arrays
	
	The maze has kMazeColumnsX columns across (20 by default) represented by an array
	We then have kMazeRowsY (20) of these arrays, one for each row
	
	Columns and rows can be confusing so we tend to prefer working with x and y
	x is the horizontal axis (columns) across and y is the vertical axis (rows) down.

	Each single item is called a cell. 
	
	E.g. to output the value of the cell at 16 X (column 16) and 1 Y (row 1) we would write:
	cout << map[1][16] << endl; // outputs G
*/

char map[kMazeRowsY][kMazeColumnsX] = {
	// 20 columns (x axis) by 20 rows (y axis)
	// X0   X1   X2   X3   X4   X5   X6   X7   X8   X9   X10  X11  X12  X13  X14  X15  X16  X17  X18  X19 
	{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },	//Y0
	{ 'W', '.', '.', '.', '.', 'W', '.', '.', '.', 'W', 'W', '.', '.', '.', '.', 'W', 'G', '.', '.', 'W' },	//Y1
	{ 'W', '.', 'W', 'W', 'W', 'W', 'W', 'W', '.', 'W', '.', '.', 'W', 'W', 'W', 'W', 'W', 'W', '.', 'W' },	//Y2
	{ 'W', '.', 'W', '.', '.', '.', 'W', '.', '.', 'W', '.', 'W', 'W', 'E', 'W', 'F', '.', '.', '.', 'W' },	//Y3
	{ 'W', '.', 'W', '.', 'W', '.', 'W', '.', 'W', 'W', '.', 'W', 'W', '.', 'W', 'W', 'W', '.', 'W', 'W' },	//Y4
	{ 'W', '.', 'W', '.', 'W', '.', '.', '.', '.', '.', '.', '.', 'W', '.', 'W', '.', '.', '.', '.', 'W' },	//Y5
	{ 'W', '.', 'W', '.', 'W', 'W', 'W', '.', '.', 'W', 'W', '.', 'W', '.', 'W', '.', 'W', '.', '.', 'W' },	//Y6
	{ 'W', '.', 'W', '.', 'W', '.', 'W', 'W', 'W', 'W', 'W', '.', 'W', '.', 'W', '.', 'W', 'W', 'W', 'W' },	//Y7
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W', '.', '.', '.', 'W', '.', '.', '.', '.', 'W' },	//Y8
	{ 'W', '.', 'W', '.', 'W', 'F', 'W', 'W', '.', 'W', 'W', 'W', '.', 'W', 'W', 'W', 'W', '.', 'W', 'W' },	//Y9
	{ 'W', '.', 'W', 'W', 'W', 'W', 'W', 'W', '.', 'W', 'W', 'W', '.', 'W', '.', 'W', 'W', '.', 'W', 'W' },	//Y10
	{ 'W', '.', '.', '.', '.', 'W', '.', '.', '.', 'W', 'W', '.', '.', '.', '.', 'W', 'F', '.', '.', 'W' },	//Y11
	{ 'W', '.', 'W', 'W', 'W', 'W', 'W', 'W', '.', '.', '.', '.', 'W', '.', 'W', 'W', 'W', 'W', '.', 'W' },	//Y12
	{ 'W', '.', 'W', '.', '.', '.', 'W', '.', '.', 'W', 'W', '.', 'W', '.', 'W', '.', '.', '.', '.', 'W' },	//Y13
	{ 'W', '.', 'W', '.', 'W', '.', 'W', '.', 'W', 'W', 'W', '.', 'W', '.', 'W', '.', 'W', 'W', 'W', 'W' },	//Y14
	{ 'W', '.', 'W', '.', 'W', '.', '.', '.', '.', 'F', 'W', '.', 'W', '.', 'W', '.', '.', '.', 'W', 'W' },	//Y15
	{ 'W', '.', 'W', '.', 'W', 'W', 'W', '.', '.', 'W', 'W', '.', 'W', '.', '.', '.', 'W', '.', '.', 'W' },	//Y16
	{ 'W', '.', 'W', '.', 'W', 'F', 'W', 'W', 'W', 'W', 'F', '.', 'W', 'W', 'W', '.', 'W', 'W', '.', 'W' },	//Y17
	{ 'W', 'P', '.', '.', '.', '.', '.', '.', '.', 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y18
	{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },	//Y19
};

char editorMap[kMazeRowsY][kMazeColumnsX] = {
	// X0   X1   X2   X3   X4   X5   X6   X7   X8   X9   X10  X11  X12  X13  X14  X15  X16  X17  X18  X19 
	{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },	//Y0
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y1
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y2
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y3
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y4
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y5
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y6
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y7
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y8
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'P', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y9
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y10
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y11
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y12
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y13
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y14
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y15
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y16
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y17
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y18
	{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },	//Y19
};

char canvas[kMazeRowsY][kMazeColumnsX] = {
	// X0   X1   X2   X3   X4   X5   X6   X7   X8   X9   X10  X11  X12  X13  X14  X15  X16  X17  X18  X19 
	{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },	//Y0
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y1
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y2
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y3
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y4
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y5
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y6
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y7
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y8
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y9
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y10
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y11
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y12
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y13
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y14
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y15
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y16
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y17
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y18
	{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },	//Y19
};

int playerY;
int playerX;
int enemyY;
int enemyX;
bool fog;
bool editor{ false };
bool win;
bool dead;

ofstream output;
ifstream input;

void SetPlayerPos()
{
	bool playerFound = false;
	for (int CellY = 0; CellY < kMazeRowsY; CellY++)
	{
		for (int CellX = 0; CellX < kMazeColumnsX; CellX++)
		{
			if (map[CellY][CellX] == 'P')
			{
				playerX = CellX;
				playerY = CellY;
				playerFound = true;
				cout << playerX << " " << playerY << endl;
			}

			if (playerFound)
			{
				break;
			}
		}
		if (playerFound)
		{
			break;
		}
	}
}

void DrawMaze()
{
	if (editor)
	{
		for (int CellY = 0; CellY < kMazeRowsY; CellY++)
		{
			for (int CellX = 0; CellX < kMazeColumnsX; CellX++)
			{
				switch (canvas[CellY][CellX])
				{
				case 'W':
					ChangeColour(100, 100, 100);
					break;
				case 'P':
					ChangeColour(50, 50, 255);
					break;
				case 'G':
					ChangeColour(255, 50, 50);
					break;
				case 'F':
					ChangeColour(255, 165, 0);
					break;
				default:
					ChangeColour(255, 255, 255);
					break;
				}
				DrawRectangle((gScreenWidth / kMazeRowsY) * CellX, (gScreenHeight / kMazeColumnsX) * CellY, gScreenWidth / kMazeRowsY, gScreenHeight / kMazeColumnsX);
			}
		}

		for (int CellY = 0; CellY < kMazeRowsY; CellY++)
		{
			for (int CellX = 0; CellX < kMazeColumnsX; CellX++)
			{
				if (map[CellY][CellX] == 'P')
				{
					DrawRectangle((gScreenWidth / kMazeRowsY) * CellX, (gScreenHeight / kMazeColumnsX) * CellY, gScreenWidth / kMazeRowsY, gScreenHeight / kMazeColumnsX);
				}
				ChangeColour(255, 200, 200);
				
			}
		}
	}
	else
	{
		if (fog)
		{
			for (int CellY = playerY - viewDistance; CellY < playerY + viewDistance + 1; CellY++)
			{
				for (int CellX = playerX - viewDistance; CellX < playerX + viewDistance + 1; CellX++)
				{
					int colorMod = 1;  // {(abs(playerX - CellX) + abs(playerY - CellY)) / 2};  //int colorMod = {(CellX) + (CellY) - abs(playerX) + abs(playerY)};
					if (colorMod < 1)
					{
						colorMod = 1;
					}
					colorMod = colorMod * colorMod;
					switch (map[CellY][CellX])
					{
					case 'W':
						ChangeColour(100 / colorMod, 100 / colorMod, 100 / colorMod);
						break;
					case 'P':
						ChangeColour(50, 50, 255);
						playerX = CellX;
						playerY = CellY;
						break;
					case 'G':
						ChangeColour(255 / colorMod, 50 / colorMod, 50 / colorMod);
						break;
					case 'F':
						ChangeColour(255 / colorMod, 165 / colorMod, 0 / colorMod);
						break;
					case 'E':
						enemyX = CellX;
						enemyY = CellY;
						ChangeColour(50 / colorMod, 255 / colorMod, 50 / colorMod);
						break;
					;			default:
						ChangeColour(255 / colorMod, 255 / colorMod, 255 / colorMod);
						break;
					}
					DrawRectangle((gScreenWidth / kMazeRowsY) * CellX, (gScreenHeight / kMazeColumnsX) * CellY, gScreenWidth / kMazeRowsY, gScreenHeight / kMazeColumnsX);
				}
			}
		}
		else
		{
			for (int CellY = 0; CellY < kMazeRowsY; CellY++)
			{
				for (int CellX = 0; CellX < kMazeColumnsX; CellX++)
				{
					switch (map[CellY][CellX])
					{
					case 'W':
						ChangeColour(100, 100, 100);
						break;
					case 'P':
						ChangeColour(50, 50, 255);
						playerX = CellX;
						playerY = CellY;
						break;
					case 'G':
						ChangeColour(255, 50, 50);
						break;
					case 'F':
						ChangeColour(255, 165, 0);
						break;
					case 'E':
						enemyX = CellX;
						enemyY = CellY;
						ChangeColour(50, 255, 50);
						break;
					;			default:
						ChangeColour(255, 255, 255);
						break;
					}
					DrawRectangle((gScreenWidth / kMazeRowsY) * CellX, (gScreenHeight / kMazeColumnsX) * CellY, gScreenWidth / kMazeRowsY, gScreenHeight / kMazeColumnsX);
				}
			}
		}
	}
	
}

void SetNewGoal()
{
	cout << "Try Set New Goal" << endl;
	bool validCell = false;

	while(validCell == false)
	{
		int xRand = rand() % kMazeColumnsX;
		int yRand = rand() % kMazeRowsY;
		if (map[yRand][xRand] == '.')
		{
			cout << "ValidCell" << endl;
			validCell = true;
			map[yRand][xRand] = 'G';
		}
	}
}

void SaveMaze(string fileName)
{
	fileName = fileName + ".txt";
	output.open(fileName);

	if (editor)
	{
		for (int CellY = 0; CellY < kMazeRowsY; CellY++)
		{
			for (int CellX = 0; CellX < kMazeColumnsX; CellX++)
			{
				output << canvas[CellY][CellX] << " ";
			}
			output << endl;
		}
	}
	else
	{
		for (int CellY = 0; CellY < kMazeRowsY; CellY++)
		{
			for (int CellX = 0; CellX < kMazeColumnsX; CellX++)
			{
				output << map[CellY][CellX] << " ";
			}
			output << endl;
		}
	}

	output.close();
	if (!output)
	{
		cerr << "File could not be opened" << endl;
	}
	else
	{
		cout << "Save Successful" << endl;
	}
}

void LoadMaze(string fileName)
{
	if (fileName == "editor")
	{
		string textInput;
		editor = true;
		cout << "To edit an existing maze, type the maze name. If you want to make a new maze, type new" << endl;
		cin >> textInput;
		if (textInput != "new")
		{
			textInput = textInput + ".txt";
			input.open(textInput);

			for (int CellY = 0; CellY < kMazeRowsY; CellY++)
			{
				for (int CellX = 0; CellX < kMazeColumnsX; CellX++)
				{
					input >> canvas[CellY][CellX];
				}
			}

			input.close();
		}
		for (int CellY = 0; CellY < kMazeRowsY; CellY++)
		{
			for (int CellX = 0; CellX < kMazeColumnsX; CellX++)
			{
				map[CellY][CellX] = editorMap[CellY][CellX];
			}
		}
	}
	else
	{
		//fog = true;
		fileName = fileName + ".txt";
		input.open(fileName);

		for (int CellY = 0; CellY < kMazeRowsY; CellY++)
		{
			for (int CellX = 0; CellX < kMazeColumnsX; CellX++)
			{
				input >> map[CellY][CellX];
			}
		}

		input.close();
		if (!input)
		{
			cerr << "File could not be opened" << endl;
		}
		else
		{
			cout << "Load Successful" << endl;
		}
	}
	
}

int points;
bool CanMoveThere(int x, int y, bool isPlayer)
{
	switch (map[x][y])
	{
	case 'W':
		return false;
		break;
	case 'G':
		win = true;
		points++;
		cout << points << endl;
		return true;
		break;
	case 'F':
		if (isPlayer == true)
		{
			dead = true;
			cout << "You are Dead" << endl;
		}
		break;
	case 'P':
		dead = true;
		cout << "You are Dead, you were eaten" << endl;
		break;
	default:
		break;
	}
}



int main()
{
	srand(time(0));
	StartClock();
	string mazeFile;
	cout << "Type maze name, if you want to make your own maze, type 'editor'" << endl;
	cin >> mazeFile;
	LoadMaze(mazeFile);
	SetPlayerPos();
	//SaveMaze(mazeFile);
	while (UpdateFramework() and dead == false)
	{
		switch (GetLastKeyPressed())
		{
		case EKeyPressed::eUp:
			if (CanMoveThere(playerY - 1, playerX, true))
			{
				map[playerY][playerX] = '.';
				playerY--;
				map[playerY][playerX] = 'P';
			}
			break;
		case EKeyPressed::eDown:
			if (CanMoveThere(playerY + 1, playerX, true))
			{
				map[playerY][playerX] = '.';
				playerY++;
				map[playerY][playerX] = 'P';
			}
			break;
		case EKeyPressed::eLeft:
			if (CanMoveThere(playerY, playerX - 1, true))
			{
				map[playerY][playerX] = '.';
				playerX--;
				map[playerY][playerX] = 'P';
			}
			break;
		case EKeyPressed::eRight:
			if (CanMoveThere(playerY, playerX + 1, true))
			{
				map[playerY][playerX] = '.';
				playerX++;
				map[playerY][playerX] = 'P';
			}
			break;
		case EKeyPressed::eSave:
			if (editor)
			{
				string input;
				cout << "Type maze name" << endl;
				cin >> input;
				SaveMaze(input);
			}
			else
			{
				output.open("SaveGame.txt");
				output << playerX << " " << playerY << endl;
				output.close();
				if (!output)
				{
					cerr << "File could not be opened" << endl;
				}
				else
				{
					cout << "Save Successful" << endl;
				}
			}
			
			break;
		case EKeyPressed::eLoad:
			map[playerY][playerX] = '.';
			input.open("SaveGame.txt");
			input >> playerX >> playerY;
			map[playerY][playerX] = 'P';
			input.close();
			if (!input)
			{
				cerr << "File could not be opened" << endl;
			}
			else
			{
				cout << "Load Successful" << endl;
			}
			break;
		case EKeyPressed::ePlaceWall:
			if (editor)
			{
				canvas[playerY][playerX] = 'W';
			}
			break;
		case EKeyPressed::ePlaceFire:
			if (editor)
			{
				canvas[playerY][playerX] = 'F';
			}
			break;
		case EKeyPressed::ePlaceEmpty:
			if (editor)
			{
				canvas[playerY][playerX] = '.';
			}
			break;
		case EKeyPressed::ePlaceGoal:
			if (editor)
			{
				canvas[playerY][playerX] = 'G';
			}
			break;
		case EKeyPressed::ePlacePlayer:
			if (editor)
			{
				canvas[playerY][playerX] = 'P';
			}
			break;

		}


		int aiInput = (rand() % 4) + 1;

		switch (aiInput)
		{
		case 1:
			if (CanMoveThere(enemyY - 1, enemyX, false))
			{
				map[enemyY][enemyX] = '.';
				enemyY--;
				map[enemyY][enemyX] = 'E';
			}
			break;
		case 2:
			if (CanMoveThere(enemyY + 1, enemyX, false))
			{
				map[enemyY][enemyX] = '.';
				enemyY++;
				map[enemyY][enemyX] = 'E';
			}
			break;
		case 3:
			if (CanMoveThere(enemyY, enemyX - 1, false))
			{
				map[enemyY][enemyX] = '.';
				enemyX--;
				map[enemyY][enemyX] = 'E';
			}
			break;
		case 4:
			if (CanMoveThere(enemyY, enemyX + 1, false))
			{
				map[enemyY][enemyX] = '.';
				enemyX++;
				map[enemyY][enemyX] = 'E';
			}
			break;
		}

		if (win == true and dead == false)
		{
			SetNewGoal();
			StartClock();
			win = false;
		}
		DrawMaze();
		cout << GetElapsedTime() << endl;
	}

	return 0;
}
