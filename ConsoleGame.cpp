#pragma region PreProcessor

#include <map>
#include <thread>
#include <vector>
#include <iostream>
#include <Windows.h>
#include <functional>
#include "Classes.h"

using namespace std;

const int width = 33;
const int height = 13;
const int centerX = (width / 2) + 1;
const int centerY = (height / 2) + 1;

#pragma region Scene A Functions and Map
void Scene1();
void SceneA1();
void SceneA2();
void SceneA3();
void SceneA4();

vector<vector<string>> scene1Map;
vector<vector<string>> sceneA1Map;
vector<vector<string>> sceneA2Map;
vector<vector<string>> sceneA3Map;
vector<vector<string>> sceneA4Map;

#pragma endregion

#pragma region Scene B Functions and Maps
void SceneB1();
void SceneB2();
void SceneB3();
void SceneB4();
vector<vector<string>> sceneB1Map;
vector<vector<string>> sceneB2Map;
vector<vector<string>> sceneB3Map;
vector<vector<string>> sceneB4Map;
#pragma endregion

#pragma region Scene C Functions and Maps
void SceneC1();
void SceneC2();
void SceneC3();
void SceneC4();
vector<vector<string>> sceneC1Map;
vector<vector<string>> sceneC2Map;
vector<vector<string>> sceneC3Map;
vector<vector<string>> sceneC4Map;
#pragma endregion


Choices availableRoads;
Pos positionPlayer = { centerX, centerY };
map<Direction, int> mapNav;

vector<vector<function<void()>>> scenes = {
	{ Scene1 },
	{ SceneA1, SceneA2, SceneA3, SceneA4 },
	{ SceneB1, SceneB2, SceneB3, SceneB4 },
	{ SceneC1, SceneC2, SceneC3, SceneC4 }
};

#pragma endregion

#pragma region Main Function

int main()
{
	SetConsoleOutputCP(65001);
	srand(time(0));


	DrawBorder(height, width);
	ToPosition(6, 3);
	string name = "";
	cout << "PICK  A  PLAYER  NAME...";
	ToPosition(6, 5);
	cout << "NAME : ";
	ToPosition(6 + 7, 5);
	getline(cin, name);
	playerSetup(name);

	
	Scene1();

	ToPosition(1, 20);
	cin.ignore();
}

#pragma endregion

//		M A I N   S C E N E
void Scene1() {
//	C O N F I G U R A T I O N S

	availableRoads = { true, true, false, true};
	system("cls");
	DrawBorder(height, width);
	scene1Map = BuildRoads(true, true, false, true);
	mapNav = {
		{Direction::up, 0},
		{Direction::down, 0},
		{Direction::left, 0},
	}; //index of scenechains
	


	// Place Indentities
	// SHOP
	ToPosition(centerX + 1, centerY + 2);
	cout << "\u2757";
	ToPosition(centerX - 2, centerY - 3);
	cout << "\u2927";

	return pickMove(scenes, availableRoads, positionPlayer, scene1Map, mapNav);
}

#pragma region Scene Chain 1

void SceneA1() {
	availableRoads = { false, true, false, true };
	system("cls");
	DrawBorder(height, width);
	sceneA1Map = BuildRoads(false, true, false, true);
	mapNav = {
		{Direction::down, -1},
		{Direction::right, 1}
	};
	
	return pickMove(scenes, availableRoads, positionPlayer, sceneA1Map, mapNav);
}

void SceneA2() {
	availableRoads = { false, false, true, true };
	system("cls");
	DrawBorder(height, width);
	sceneA2Map = BuildRoads(false, false, true, true);
	mapNav = {
		{Direction::left, 0},
		{Direction::right, 2}
	};

	return pickMove(scenes, availableRoads, positionPlayer, sceneA2Map, mapNav);
}

void SceneA3() {
	system("cls");
	availableRoads = { true, false, true, false };
	DrawBorder(height, width);
	sceneA3Map = BuildRoads(true, false, true, false);
	mapNav = {
		{Direction::up, 3},
		{Direction::left, 1}
	};

	return pickMove(scenes, availableRoads, positionPlayer, sceneA3Map, mapNav);
}


void SceneA4() {
	system("cls");
	availableRoads = { false, true, false, false };
	DrawBorder(height, width);
	sceneA4Map = BuildRoads(false, true, false, false);
	mapNav = {
		{Direction::down, 2}
	};

	return pickMove(scenes, availableRoads, positionPlayer, sceneA4Map, mapNav);
}

#pragma endregion

#pragma region Scene Chain 2

void SceneB1() {
	system("cls");
	availableRoads = { true, false, true, false };
	DrawBorder(height, width);
	sceneB1Map = BuildRoads( true, false, true, false );
	mapNav = {
		{Direction::up, -1},
		{Direction::left, 1}
	};

	return pickMove(scenes, availableRoads, positionPlayer, sceneB1Map, mapNav);
}

void SceneB2() {
	system("cls");
	availableRoads = { false, true, false, true };
	DrawBorder(height, width);
	sceneB2Map = BuildRoads( false, true, false, true );
	mapNav = {
		{Direction::right, 0},
		{Direction::down, 2}
	};

	return pickMove(scenes, availableRoads, positionPlayer, sceneB2Map, mapNav);
}

void SceneB3() {
	system("cls");
	availableRoads = { true, false, true, false };
	DrawBorder(height, width);
	sceneB3Map = BuildRoads(true, false, true, false);
	mapNav = {
		{Direction::up, 1},
		{Direction::left, 3}
	};

	return pickMove(scenes, availableRoads, positionPlayer, sceneB3Map, mapNav);
}

void SceneB4() {
	system("cls");
	availableRoads = { false, false, false, true };
	DrawBorder(height, width);
	sceneB4Map = BuildRoads(false, false, false, true);
	mapNav = {
		{Direction::right, 2}
	};

	return pickMove(scenes, availableRoads, positionPlayer, sceneB4Map, mapNav);
}

#pragma endregion

#pragma region Scene Chain 3

void SceneC1() {
	system("cls");
	availableRoads = { false, false, true, true };
	DrawBorder(height, width);
	sceneC1Map = BuildRoads(false, false, true, true);
	mapNav = {
		{Direction::left, -1},
		{Direction::right, 1}
	};

	return pickMove(scenes, availableRoads, positionPlayer, sceneC1Map, mapNav);
}

void SceneC2() {
	system("cls");
	availableRoads = { false, true, true, false };
	DrawBorder(height, width);
	sceneC2Map = BuildRoads(false, true, true, false);
	mapNav = {
		{Direction::left, 0},
		{Direction::down, 2}
	};

	return pickMove(scenes, availableRoads, positionPlayer, sceneC2Map, mapNav);
}

void SceneC3() {
	system("cls");
	availableRoads = { true, true, false, false };
	DrawBorder(height, width);
	sceneC3Map = BuildRoads(true, true, false, false);
	mapNav = {
		{Direction::up, 1},
		{Direction::down, 3}
	};

	return pickMove(scenes, availableRoads, positionPlayer, sceneC3Map, mapNav);
}

void SceneC4() {
	system("cls");
	availableRoads = { true, false, false, false };
	DrawBorder(height, width);
	sceneC4Map = BuildRoads(true, false, false, false);
	mapNav = {
		{Direction::up, 2}
	};

	return pickMove(scenes, availableRoads, positionPlayer, sceneC4Map, mapNav);
}

#pragma endregion