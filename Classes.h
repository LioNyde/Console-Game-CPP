#pragma once

#include <functional>
#include <iostream>
#include <vector>

using namespace std;

// GLOBAL VARIABLES
extern const int width;
extern const int height;
extern const int centerX;
extern const int centerY;
extern HANDLE color;

struct Pos {
	int x;
	int y;

	bool operator==(const Pos& other) const {
		return x == other.x && y == other.y;
	}
	bool operator!=(const Pos& other) const {
		return x != other.x || y != other.y;
	}
};

struct NPC {
	string Name;
	string Identity;
	Pos Position;
	function<void()> Interact;
};


struct Choices {
	bool up;
	bool down;
	bool left;
	bool right;
};

struct Scenes {
	function<void()>
};

class Player {
public:
	Pos currentPosition;
	//vector<Items> inventory;
	float Health;
	Player(Pos currPosition, float health);
};



void pickMove(vector<vector<function<void()>>> choices, Choices roadsAvailable, Pos& playerpos, vector<vector<string>> mapdata);
void ToPosition(int x, int y);
void DrawBorder(int height, int width);
vector<vector<string>> BuildRoads(bool up, bool down, bool left, bool right);
