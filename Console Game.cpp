#pragma region PreProcessor

#include <thread>
#include <vector>
#include <iostream>
#include <Windows.h>
#include <functional>

#include "Classes.h"

using namespace std;

bool firstTime = true;
const int width = 33;
const int height = 13;
const int centerX = (width / 2) + 1;
const int centerY = (height / 2) + 1;


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

Choices availableRoads;

Pos positionPlayer = { centerX, centerY };
Player Steve(positionPlayer, 100);

HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
//vector<function<void()>> scenes = { SceneA1, SceneA2, SceneA3, SceneA4 };
vector<vector<function<void()>>> scenes = {
	{ Scene1 },
	{ SceneA1, SceneA2, SceneA3, SceneA4 }
};

#pragma endregion

#pragma region Main Function

int main()
{
	SetConsoleOutputCP(65001);
	
	cout << "START?";
	cin.ignore();
	system("cls");


	Scene1();


	ToPosition(1, 20);
	cin.ignore();
}

#pragma endregion

#pragma region NPCs

void ShopTalk() {
	cout << "This is shop...";
}

void swordDealer() {
	cout << "This is sword dealer...";
}

NPC shop = { "Shop", "\u2757", {centerX + 3, centerY + 3}, ShopTalk};
NPC sworddealer = { "Sword Dealer", "\u2927", {centerX - 3, centerY - 2}, swordDealer};

#pragma endregion


//	VILLAGE
void Scene1() {
//	C O N F I G U R A T I O N S

	availableRoads = { true, false, true, true};
	system("cls");
	DrawBorder(height, width);
	scene1Map = BuildRoads(true, false, true, true);


	// Place Indentities
	ToPosition(shop.Position.x, shop.Position.y);
	cout << shop.Identity;
	ToPosition(sworddealer.Position.x, sworddealer.Position.y);
	cout << sworddealer.Identity;

	return pickMove(scenes, availableRoads, positionPlayer, scene1Map);
}

void SceneA1() {
	availableRoads = { false, true, false, true };
	system("cls");
	DrawBorder(height, width);
	sceneA1Map = BuildRoads(false, true, false, true);
	cin.ignore();
	
	return pickMove(scenes, availableRoads, positionPlayer, sceneA1Map);
}

void SceneA2() {
	availableRoads = { false, false, true, true };
	system("cls");
	DrawBorder(height, width);
	sceneA2Map = BuildRoads(false, false, true, true);
	
	return pickMove(scenes, availableRoads, positionPlayer, sceneA2Map);
}

void SceneA3() {
	availableRoads = { true, false, true, false };
	system("cls");
	DrawBorder(height, width);
	scene1Map = BuildRoads(true, false, true, false);
	cin.ignore();
	return SceneA4();
}

void SceneA4() {
	availableRoads = { false, true, false, false };
	system("cls");
	DrawBorder(height, width);
	scene1Map = BuildRoads(false, true, false, false);
	cin.ignore();
}