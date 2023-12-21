#include <functional>
#include <Windows.h>
#include <iostream>
#include <vector>

#include "Classes.h"

string playerID = "\u2b22";

using namespace std;

Pos centerPoint = { centerX, centerY };
Pos pointUp = { centerX, 2 };
Pos pointDown = { centerX, centerY * 2 - 2 };
Pos pointLeft = { 2, centerY };
Pos pointRight = { centerX * 2 - 2, centerY };


Player::Player(Pos currPosition, float health) {
	this->currentPosition = currPosition;
	this->Health = health;
}

void ToPosition(int x, int y) {
	HANDLE cursor = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { (SHORT)x - 1 , (SHORT)y - 1 };
	SetConsoleCursorPosition(cursor, pos);
}

void Move(Pos posPlayer, Pos newPos, vector<vector<string>> mapdata) {
	int colorNum = (posPlayer == centerPoint ||
		posPlayer == pointUp ||
		posPlayer == pointDown ||
		posPlayer == pointLeft ||
		posPlayer == pointRight) ? 7 : 8;


	if (posPlayer.x == newPos.x) {
		if (posPlayer.y > newPos.y) {
			while (posPlayer.y != newPos.y) {
				ToPosition(posPlayer.x, posPlayer.y);
				cout << playerID;
				Sleep(130);
				ToPosition(posPlayer.x, posPlayer.y);
				SetConsoleTextAttribute(color, colorNum);
				cout << mapdata[posPlayer.y][posPlayer.x];
				SetConsoleTextAttribute(color, 7);
				posPlayer.y--;
			}
		}else if(posPlayer.y < newPos.y){
			while (posPlayer.y != newPos.y) {
				ToPosition(posPlayer.x, posPlayer.y);
				cout << playerID;
				Sleep(130);
				ToPosition(posPlayer.x, posPlayer.y);
				SetConsoleTextAttribute(color, colorNum);
				cout << mapdata[posPlayer.y][posPlayer.x];
				SetConsoleTextAttribute(color, 7);
				posPlayer.y++;
			}
		}
		return;
	}
	if (posPlayer.y == newPos.y) {
		if (posPlayer.x > newPos.x) {
			while (posPlayer.x != newPos.x) {
				ToPosition(posPlayer.x, posPlayer.y);
				cout << playerID;
				Sleep(130);
				ToPosition(posPlayer.x, posPlayer.y);
				SetConsoleTextAttribute(color, colorNum);
				cout << mapdata[posPlayer.y][posPlayer.x];
				SetConsoleTextAttribute(color, 7);
				posPlayer.x--;
			}
		}
		else if (posPlayer.x < newPos.x) {
			while (posPlayer.x != newPos.x) {
				ToPosition(posPlayer.x, posPlayer.y);
				cout << playerID;
				Sleep(130);
				ToPosition(posPlayer.x, posPlayer.y);
				SetConsoleTextAttribute(color, colorNum);
				cout << mapdata[posPlayer.y][posPlayer.x];
				SetConsoleTextAttribute(color, 7);
				posPlayer.x++;
			}
		}
	}
}

            									 //    index
int canContinueMove(Pos& playerpos, Choices roads, int currScene, int input, vector<vector<string>> mapdata) {
//		CENTER POINT  ||  Position of Player
	if (playerpos == centerPoint) {
		switch (input) {
		case 1: // move up
			// Move Function
			if (!roads.up) {
				ToPosition(width + 6, 10);
				cout << "Cant do that!!";
				Sleep(500);
				ToPosition(width + 6, 10);
				cout << "                               ";
				break;
			}
			Move(playerpos, pointUp, mapdata);
			playerpos = pointUp;
			input = 0;
			break;
		case 2: 
			// Move Function
			if (!roads.down) {
				ToPosition(width + 6, 10);
				cout << "Cant do that!!";
				Sleep(500);
				ToPosition(width + 6, 10);
				cout << "                               ";
				break;
			}
			Move(playerpos, pointDown, mapdata);
			playerpos = pointDown;
			input = 0;
			break;
		case 3:
			// Move Function
			if (!roads.left) {
				ToPosition(width + 6, 10);
				cout << "Cant do that!!";
				Sleep(500);
				ToPosition(width + 6, 10);
				cout << "                               ";
				break;
			}
			Move(playerpos, pointLeft, mapdata);
			playerpos = pointLeft;
			input = 0;
			break;
		case 4: // move up
			// Move Function
			if (!roads.right) {
				ToPosition(width + 6, 10);
				cout << "Cant do that!!";
				Sleep(500);
				ToPosition(width + 6, 10);
				cout << "                               ";
				break;
			}
			Move(playerpos, pointRight, mapdata);
			playerpos = pointRight;
			input = 0;
			break;
		}
	}
//		POINT UP  ||  Position of Player
	if (playerpos == pointUp) {
		switch (input) {
		case 1:
		case 3:
		case 4:
			ToPosition(width + 6, 10);
			cout << "Cant do that!!";
			Sleep(500);
			ToPosition(width + 6, 10);
			cout << "                               ";
			break; 
		case 2:
			// Move Function
			Move(playerpos, centerPoint, mapdata);
			playerpos = centerPoint;
			break;
		}
	}
//		POINT DOWN  ||  Position of Player
	if (playerpos == pointDown) {
		switch (input) {
		case 1:
			// Move Function
			Move(playerpos, centerPoint, mapdata);
			playerpos = centerPoint;
			break;
		case 2:
		case 3:
		case 4:
			ToPosition(width + 6, 10);
			cout << "Cant do that!!";
			Sleep(500);
			ToPosition(width + 6, 10);
			cout << "                               ";
			break;
		}
	}

//		POINT LEFT  ||  Position of Player
	if (playerpos == pointLeft) {
		switch (input) {
		case 1:
		case 2:
		case 3:
			ToPosition(width + 6, 10);
			cout << "Cant do that!!";
			Sleep(500);
			ToPosition(width + 6, 10);
			cout << "                               ";
			break;
		case 4:
			// Move Function
			Move(playerpos, centerPoint, mapdata);
			playerpos = centerPoint;
			break;
		}
	}
//		POINT RIGHT  ||  Position of Player
	if (playerpos == pointRight) {
		switch (input) {
		case 1:
		case 2:
		case 4:
			ToPosition(width + 6, 10);
			cout << "Cant do that!!";
			Sleep(500);
			ToPosition(width + 6, 10);
			cout << "                               ";
			break;
		case 3:
			// Move Function
			Move(playerpos, centerPoint, mapdata);
			playerpos = centerPoint;
			break;
		}
	}

	return 0;
}

void pickMove(vector<vector<function<void()>>> scenes, Choices roads, Pos& playerpos, vector<vector<string>> mapData) {

	int currentScene = 0;
	int indent = width + 6;
	int movepick = 0;


//		D I S P L A Y    P L A Y E R
	ToPosition(playerpos.x, playerpos.y);
	cout << playerID;

//		D I S P L A Y    C H O I C E S
	ToPosition(indent, 2);
	cout << "1) Move Up";
//  -------------------------------
	ToPosition(indent, 3);
	cout << "2) Move Down";
//  -------------------------------
	ToPosition(indent, 4);
	cout << "3) Move Left";
//  -------------------------------
	ToPosition(indent, 5);
	cout << "4) Move Right";
	ToPosition(indent, 6);
	cout << "5) Interact";

	ToPosition(indent, 7);
	cout << "                      ";
	ToPosition(indent, 7);
	cout << "Choose an action : ";
	cin >> movepick;

	

	switch (movepick) {
	case 1:
		canContinueMove(playerpos, roads, currentScene, movepick, mapData);
		break;
	case 2:
		canContinueMove(playerpos, roads, currentScene, movepick, mapData);
		break;
	case 3:
		canContinueMove(playerpos, roads, currentScene, movepick, mapData);
		break;
	case 4:
		canContinueMove(playerpos, roads, currentScene, movepick, mapData);
		break;
	}
	pickMove(scenes, roads, playerpos, mapData);
}

void DrawBorder(int height, int width) {
	int xPos = 1;
	string borderTop = "\u2584";
	string borderBot = "\u2580";
	string borderSide = "\u2588";

//	BORDER TOP
	while (xPos <= width) {
		ToPosition(xPos, 0);
		SetConsoleTextAttribute(color, 11); // set colors
		cout << borderTop;
		SetConsoleTextAttribute(color, 7);  // set colors
		xPos++;
	}

	xPos = 0;
// BORDER LEFT
	int yPos = 1;
	while (yPos <= height - 1) {
		ToPosition(1, yPos  + 1);
		SetConsoleTextAttribute(color, 11);  // set colors
		cout << borderSide;
		SetConsoleTextAttribute(color, 7);
		yPos++;
	}

//	BORDER BOTTOM
	yPos = 1;
	while (xPos <= width) {
		ToPosition(xPos, height);
		SetConsoleTextAttribute(color, 11);  // set colors
		cout << borderBot;
		SetConsoleTextAttribute(color, 7);  // set colors
		xPos++;
	}

//	BORDER RIGHT
	while (yPos <= height - 2) {
		ToPosition(width, yPos + 1); 
		SetConsoleTextAttribute(color, 11);  // set colors
		cout << borderSide;
		SetConsoleTextAttribute(color, 7);  // set colors
		yPos++;
	}
	
}


vector<vector<string>> BuildRoads(bool up, bool down, bool left, bool right) {
	vector<vector<string>> mapIdentity(13, vector<string>(33, " "));

	string roadY = "\u2503";
	string roadX = "\u2500";

	// Place center point
	ToPosition(centerX, centerY);
	cout << 1;
	mapIdentity[centerY][centerX] = "1";

	// Get the number between numbers in map and center point
	ToPosition(23, 23);
	int roadsizeX = (width - centerX) - 2;
	int roadsizeY = (height - centerY) - 2;

	// right road
	if (right) {
		ToPosition(centerX * 2 - 2, centerY);
		cout << 2;
		mapIdentity[centerY][static_cast<int64_t>(centerX) * 2 - 2] = "2";

		for (int i = 1; i <= roadsizeX; i++) {
			ToPosition(centerX + i, centerY);
			SetConsoleTextAttribute(color, 8);
			cout << roadX;
			SetConsoleTextAttribute(color, 7);
			mapIdentity[centerY][static_cast<int64_t>(centerX) + i] = roadX;
		}
	}

	// left road
	if (left) {
		ToPosition(2, centerY);
		cout << 3;

		for (int i = 1; i <= roadsizeX; i++) {
			ToPosition(2 + i, centerY);
			SetConsoleTextAttribute(color, 8);
			cout << roadX;
			SetConsoleTextAttribute(color, 7);
			mapIdentity[centerY][static_cast<int64_t>(2) + i] = roadX;
		}
		mapIdentity[centerY][2] = "3";
	}

	// upper road
	if (up) {
		ToPosition(centerX, 2);
		cout << 4;

		for (int i = 1; i <= roadsizeY; i++) {
			ToPosition(centerX, 2 + i);
			SetConsoleTextAttribute(color, 8);
			cout << roadY;
			SetConsoleTextAttribute(color, 7);
			mapIdentity[static_cast<int64_t>(2) + i][centerX] = roadY;
		}
		mapIdentity[2][centerX] = "4";
	}

	// lower road
	if (down) {
		ToPosition(centerX, centerY * 2 - 2);
		cout << 5;

		for (int i = 1; i <= roadsizeY; i++) {
			ToPosition(centerX, centerY + i);
			SetConsoleTextAttribute(color, 8);
			cout << roadY;
			SetConsoleTextAttribute(color, 7);
			mapIdentity[static_cast<int64_t>(centerY) + i][centerX] = roadY;
		}
		mapIdentity[static_cast<int64_t>(centerY) * 2 - 2][centerX] = "5";
	}

	return mapIdentity;
}