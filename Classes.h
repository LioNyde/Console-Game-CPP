#pragma once

#include <functional>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

// GLOBAL VARIABLES
extern const int width;
extern const int height;
extern const int centerX;
extern const int centerY;


enum class Direction {
	up, down, left, right
};

struct Road {
	Direction direction;
	int targetScene;
	string name;
};

struct Pos {
	int x;
	int y;

	bool operator==(const Pos& other) const {
		return x == other.x && y == other.y;
	}
	bool operator!=(const Pos& other) const {
		return x != other.x || y != other.y;
	}
	bool operator<(const Pos& rhs) const {
		if (x == rhs.x) {
			return y < rhs.y;
		}
		else {
			return x < rhs.x;
		}
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


class Player {
public:
	Pos currentPosition;
	//vector<Items> inventory;
	float Health;
	Player(Pos currPosition, float health);
};



void pickMove(vector<vector<function<void()>>> scenes, Choices roadsAvailable, Pos& playerpos, vector<vector<string>> mapdata, map<Direction, int> scenenav);
void ToPosition(int x, int y);
void DrawBorder(int height, int width);
vector<vector<string>> BuildRoads(bool up, bool down, bool left, bool right);