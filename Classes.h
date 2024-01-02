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


struct Choices {
	bool up;
	bool down;
	bool left;
	bool right;
};

struct Range {
	int min;
	int max;
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

enum class Arms {
	fist, sword, axe, hammer
};


class Weapon{
public:
	string name;
	int value;
	Range damage;
	Weapon(string name, int value, Range damage) : name(name), value(value), damage(damage) {
	}
};



class Player {
public:
	string name;
	int health;
	Weapon* equipped;
	int killCount;
	int maxHp;

	Player(string, int);
};

struct Enemy {
	string name;
	int health;
	int atkPower;
	Range rewards;
};

Enemy spawnEnemy(int index);
void ToPosition(int x, int y);
void playerSetup(string name);
void DrawBorder(int height, int width);
void dispTuts(Player& p, vector<vector<function<void()>>> scenes);
vector<vector<string>> BuildRoads(bool up, bool down, bool left, bool right);
void pickMove(vector<vector<function<void()>>> scenes, Choices roadsAvailable, Pos& playerpos, vector<vector<string>> mapdata, map<Direction, int> scenenav);
