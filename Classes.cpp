#pragma region Initialization and Declarations

#include <functional>
#include <Windows.h>
#include <iostream>
#include <iterator>
#include <cstdlib>
#include <random>
#include <string>
#include <vector>
#include <map>
#include "Classes.h"

using namespace std;

bool doRepeat;
int sindex = 0; // scene index
int sidx = 0;
string playerID = "\u2b22";
Pos centerPoint = { centerX, centerY };
Pos pointUp = { centerX, 2 };
Pos pointDown = { centerX, centerY * 2 - 2 };
Pos pointLeft = { 2, centerY };
Pos pointRight = { centerX * 2 - 2, centerY };

HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);



#pragma endregion


#pragma region Extra Values and Functions

map<Pos, Pos> reversePosition = {
	{pointUp, pointDown},
	{pointDown, pointUp},
	{pointLeft, pointRight},
	{pointRight, pointLeft}
};


/// <summary>
/// Places the cursor to any position on the windows console.
/// </summary>
/// <param name="x">axis position</param>
/// <param name="y">axis position</param>
void ToPosition(int x, int y) {
	HANDLE cursor = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { (SHORT)x - 1 , (SHORT)y - 1 };
	SetConsoleCursorPosition(cursor, pos);
}


#pragma endregion


#pragma region Enemy

int random_0_to_n(int n);
enum class agros {
	none, blob, boar, skeleton, draugr, goblin, troll
};

Enemy spawnEnemy(int index) {
	map<agros, Enemy> hostiles;

	if (index != 1 && index != 2 && index != 3) {
		return { "", 0, 0, {0, 0} };
	}
	if (index == 1) {
		hostiles = {
			{agros::none, {"", 0, 0, {0, 0}}},
			{agros::none, {"", 0, 0, {0, 0}}},
			{agros::none, {"", 0, 0, {0, 0}}},
			{agros::blob, {"Blob", 15, 5, {2, 6}}},
			{agros::none, {"", 0, 0, {0, 0}}},
			{agros::boar, {"Boar", 25, 6, {4, 7}}}
		};
	}
	if (index == 2) {
		hostiles = {
			//{agros::none, {"", 0, 0, {0, 0}}}, add more of this to increase battle free
			{agros::skeleton, {"Skeleton", 35, 13, {13, 18}}},
			{agros::none, {"", 0, 0, {0, 0}}},
			{agros::draugr, {"Draugr", 40, 16, {14, 20}}},
			{agros::none, {"", 0, 0, {0, 0}}},
			{agros::none, {"", 0, 0, {0, 0}}}
		};
	}
	if (index == 3) {
		hostiles = {
			{agros::none, {"", 0, 0, {0, 0}}},
			{agros::none, {"", 0, 0, {0, 0}}},
			{agros::goblin, {"Goblin", 35, 13, {13, 18}}},
			{agros::troll, {"Troll", 40, 16, {14, 20}}},
			{agros::none, {"", 0, 0, {0, 0}}},
			{agros::none, {"", 0, 0, {0, 0}}},
		};
	}
	
	
	map<agros, Enemy>::iterator spawn = hostiles.begin();
	advance(spawn, random_0_to_n(hostiles.size() - 1));
	return spawn->second;
}

int random_0_to_n(int n) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, n);
	return dis(gen);
}

#pragma endregion


#pragma region Player Values


map<Arms, Weapon*> weapons;
Weapon* getWeapon(Arms arm) {
	// Try to insert a null pointer into the map for the given arm
	auto result = weapons.insert({ arm, nullptr });

	// If the insertion succeeded (the arm was not already in the map)
	if (result.second) {
		// Create a new Weapon and assign it to the inserted pointer
		switch (arm) {
		case Arms::fist:
			result.first->second = new Weapon("Fist", 0, { 4, 6});
			break;
		case Arms::sword:
			result.first->second = new Weapon("Sword", 12, { 6, 9 });
			break;
		case Arms::axe:
			result.first->second = new Weapon("Axe", 14, { 8, 13 }); 
			break;
		case Arms::hammer:
			result.first->second = new Weapon("Hammer", 16, { 16, 19 });
			break;
		}
	}

	// Return the weapon associated with the arm
	return result.first->second;
}


Player::Player(string n, int h) : name(n), health(h) {
	killCount = 0;
	equipped = getWeapon(Arms::fist);
	maxHp = h;
	health = maxHp;
}



#pragma endregion


#pragma region NPC


	void dispTuts(Player &p, vector<vector<function<void()>>> scenes) {
		system("cls");
		DrawBorder(height, 65);

		ToPosition(3, 3);
		cout << "Ur character is " << playerID;
		ToPosition(3, 4);
		cout << "Its better to head up north first for easy enemies.";
		ToPosition(3, 5);
		cout << "So it is better to read what u can do";

		ToPosition(3, 6);
		cout << "Using defense battle reduces incoming damange by .25";

		ToPosition(3, 7);
		cout << "Going to wrong direction has a big chance to engage a battle.";

		ToPosition(3, 8);
		cout << "You have 1/5th chance to successfully escape a fight.";

		ToPosition(3, 9);
		cout << "On every 5 kills u have, your health is increased by 10";
		

		ToPosition(3, 11);
		cout << "Press Enter to Continue";
		system("pause");
		return scenes[sindex][sidx]();
	}

	void interactWarMaster(Player &p, vector<vector<function<void()>>> scenes) {
		system("cls");
		DrawBorder(height, 40);

		ToPosition(3, 3);
		cout << "Which One you want to unlock? : ";
		ToPosition(3, 4);
		cout << "Current Kills : " << p.killCount;

		ToPosition(3, 6);
		cout << "1. Sword : 8 kills";
		ToPosition(3, 7);
		cout << "2. Axe : 10 kills";
		ToPosition(3, 8);
		cout << "3. Hammer : 15 kills";

		ToPosition(3, 10);
		cout << "4. Leave";

		ToPosition(3 + 32 , 3);
		int pick;
		cin >> pick;

		switch (pick) {
		case 1:
			if (p.killCount >= 8) {
				p.equipped = getWeapon(Arms::sword);
				ToPosition(3, 2);
				cout << "Weapon changed to " << p.equipped->name;
			}else {
				ToPosition(3, 2);
				cout << "Go and get More KIlls";
			}
			Sleep(2000);
			break;
		case 2:
			if (p.killCount >= 10) {
				p.equipped = getWeapon(Arms::sword);
				ToPosition(3, 2);
				cout << "Weapon changed to " << p.equipped->name;
			}
			else {
				ToPosition(3, 2);
				cout << "Go and get More KIlls";
			}
			Sleep(2000);
			break;
		case 3:
			if (p.killCount >= 15) {
				p.equipped = getWeapon(Arms::sword);
				ToPosition(3, 2);
				cout << "Weapon changed to " << p.equipped->name;
			}
			else {
				ToPosition(3, 2);
				cout << "Go and get More KIlls";
			}
			Sleep(2000);
			break;
		case 4:
			return scenes[sindex][sidx]();
		}
		return scenes[sindex][sidx]();;
	}

#pragma endregion


#pragma region Player and Enemy

bool inFight = false;
Player player("", 20);
void playerSetup(string name) {
	player.name = name;
}

Enemy encounter;


void startFight(Player &player, Enemy &enemy, vector<vector<function<void()>>> scenes, Pos &posP) {
	system("cls");
	ToPosition(1, 1);


	//scenes[sindex][sidx]();
	
	DrawBorder(height, width);
	ToPosition(6, centerY);
	cout << "Engaging in Battle...";
	Sleep(1500);
	ToPosition(6, centerY);
	cout << "                       ";

	cin.ignore();

	int y = 2;
	while (y <= height - 1) {
		ToPosition(centerX, y);
		cout << "|";
		y++;
	}

	// Display player infos
	int pit = 3; //indent
	int eit = centerX + 2;
	ToPosition(pit, 3);
	cout << player.name;
	
	ToPosition(pit, 5);
	cout << "Life : " << player.health;
	ToPosition(pit, 6);
	cout << "Weapon : " << player.equipped->name;
	ToPosition(pit, 7);
	cout << "Damage : " << player.equipped->damage.min << "-" << player.equipped->damage.max;

	//Display enemy infos
	
	ToPosition(eit, 3);
	cout << enemy.name;
	
	ToPosition(eit, 5);
	cout << "Life : " << enemy.health;
	ToPosition(eit, 6);
	cout << "Weapon : " << enemy.atkPower;


	int starter = (random_0_to_n(2) > 0) ? 1 : 0; //1 for player
	


	// start fighting
	bool fighting = true;
	bool pdefense = false;
	bool edefense = false;

	while (fighting) {
		ToPosition(width + 6, 2); // position for logs
		cout << "                                         ";
		ToPosition(width + 6, 2); // position for logs
		if (starter == 1)
			cout << player.name << " 's Turn!";
		else
			cout << enemy.name << " 's Turn!";


		//  PLAYER TURN
		if (starter == 1) {
			ToPosition(width + 6, 9);
			cout << "                                        ";
			ToPosition(width + 6, 9);
			cout << "Pick an action : ";
			
			ToPosition(width+6, 4);
			cout << "1. Attack";
			ToPosition(width + 6, 5);
			cout << "2. Defend"; // reduce incomming damage
			ToPosition(width + 6, 6);
			cout << "3. Escape"; // have a chance to do so and punished if failed
			


			int atkOpt;
			ToPosition(width + 6 + 17, 9);
			cin >> atkOpt;
			switch (atkOpt) {
			case 1:
			{
				ToPosition(width + 6, 2);
				cout << "                                  ";
				ToPosition(width + 6, 2);
				cout << player.name << " uses attack!"; // log

				int randDmg = rand() % (player.equipped->damage.max - player.equipped->damage.min + 1) + player.equipped->damage.min;
				int calculateDmg = randDmg;
				if (edefense == true) {
					calculateDmg = randDmg * .75;
					edefense = false;
				}
				enemy.health = ((enemy.health - calculateDmg) >= 0) ? enemy.health - calculateDmg : 0;


				Sleep(1500);
				// update health
				ToPosition(eit, 5);
				cout << "           ";
				ToPosition(eit, 5);
				cout << "Life : " << enemy.health;

				// log
				ToPosition(width + 6, 2);
				cout << "                                         ";
				ToPosition(width + 6, 2);
				cout << enemy.name << " took " << calculateDmg << " damage";
				break;
			}
			case 2:
				pdefense = true;
				if (edefense)
					edefense = false;
				ToPosition(width + 6, 2);
				cout << "                                  ";
				ToPosition(width + 6, 2);
				cout << player.name << "'s defense on!";
				break;
			case 3:
				int doLeave = rand() % (5 - 1) + 1;
				if (doLeave == 2) {
					ToPosition(width + 6, 2);
					cout << "                                  ";
					ToPosition(width + 6, 2);
					cout << "You escaped successfully.";
					fighting = false;
				}
				else {
					ToPosition(width + 6, 2);
					cout << "                                  ";
					ToPosition(width + 6, 2);
					cout << "You failed to escape.";
				}
			}
		}

		// ENEMY TURN
		if (starter == 0) { // for enemy
			int randAtk = rand() % (5 - 1) + 1;
			cout << randAtk;
			switch (randAtk) {
			case 1:
			case 2:
				// defend receive only 3/4 of dmaage
				ToPosition(width + 6, 2);
				cout << "                                  ";
				ToPosition(width + 6, 2);
				cout << enemy.name << "'s defense on!";

				edefense = true;
				if (pdefense)
					pdefense = false;
				break;
			case 3:
			case 4:
			case 5:
				//attack
				ToPosition(width + 6, 2);
				cout << "                                  ";
				ToPosition(width + 6, 2);
				cout << enemy.name << " uses attack!";

				int dmg = enemy.atkPower;
				if (pdefense) {
					dmg *= .75;
					pdefense = false;
				}
				player.health = ((player.health - dmg) >= 0) ? player.health - dmg : 0;


				Sleep(1500);
				// log
				ToPosition(width + 6, 2);
				cout << "                                         ";
				ToPosition(width + 6, 2);
				cout << player.name << " took " << dmg << " damage.";


				// update health
				ToPosition(pit, 5);
				cout << "           ";
				ToPosition(pit, 5);
				cout << "Life : " << player.health;
				break;
			}
		}
		starter = (starter == 1) ? 0 : 1;
		if (enemy.health == 0 || player.health == 0) {
			if (enemy.health <= 0) {
				player.killCount = player.killCount + 1;
			}
			if (player.health <= 0) {
				sidx = 0;
				sindex = 0;
				posP = centerPoint;
			}
			fighting = false;
		}
		Sleep(2500);
	}

	if ((player.killCount % 5) == 0 && player.killCount > 0) {
		player.maxHp = player.maxHp + 10;
	}

	inFight = false;
	player.health = player.maxHp;
	return scenes[sindex][sidx]();

}

#pragma endregion


#pragma region Movement System and Calculation

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


bool canContinueMove(Pos& playerpos, Choices roads, int input, vector<vector<string>> mapdata, Direction &walkpast) {
	bool doreturn = false;
//		CENTER POINT  ||  Position of Player
	if (playerpos == centerPoint) {
		switch (input) {
		case 1: // move up
		{
			// Move Function
			if (!roads.up) {
				ToPosition(width + 6, 10);
				cout << "Watch Out!!";
				Sleep(500);
				ToPosition(width + 6, 10);
				cout << "                               ";

				encounter = spawnEnemy(sindex);
				if (encounter.name != "") {
					ToPosition(1, height + 4);
					cout << encounter.name;
					inFight = true;
					doreturn = true;
					break;
				}
				break;
			}
			Move(playerpos, pointUp, mapdata);
			playerpos = pointUp;
			input = 0;
			int fchance = rand() % (20 - 1) + 1;
			if (fchance >= 5 && fchance <= 9) {
				encounter = spawnEnemy(sindex);
				if (encounter.name != "") {
					inFight = true;
					doreturn = true;
					break;
				}
			}
			break;
		}
		case 2:
		{
			// Move Function
			if (!roads.down) {
				ToPosition(width + 6, 10);
				cout << "Watch Out!!";
				Sleep(500);
				ToPosition(width + 6, 10);
				cout << "                               ";

				encounter = spawnEnemy(sindex);
				if (encounter.name != "") {
					inFight = true;
					doreturn = true;
					break;
				}
				break;
			}
			Move(playerpos, pointDown, mapdata);
			playerpos = pointDown;
			input = 0;
			int fchance = rand() % (20 - 1) + 1;
			if (fchance >= 5 && fchance <= 9) {
				encounter = spawnEnemy(sindex);
				if (encounter.name != "") {
					inFight = true;
					doreturn = true;
					break;
				}
			}
			break;
		}
		case 3:
		{
			// Move Function
			if (!roads.left) {
				ToPosition(width + 6, 10);
				cout << "Watch Out!!";
				Sleep(500);
				ToPosition(width + 6, 10);
				cout << "                               ";

				encounter = spawnEnemy(sindex);
				if (encounter.name != "") {
					inFight = true;
					doreturn = true;
					break;
				}
				break;
			}
			Move(playerpos, pointLeft, mapdata);
			playerpos = pointLeft;
			input = 0;
			int fchance = rand() % (20 - 1) + 1;
			if (fchance >= 5 && fchance <= 9) {
				encounter = spawnEnemy(sindex);
				if (encounter.name != "") {
					inFight = true;
					doreturn = true;
					break;
				}
			}
			break;
		}
		case 4: // move up
		{
			// Move Function
			if (!roads.right) {
				ToPosition(width + 6, 10);
				cout << "Watch Out!!";
				Sleep(500);
				ToPosition(width + 6, 10);
				cout << "                               ";

				encounter = spawnEnemy(sindex);
				if (encounter.name != "") {
					inFight = true;
					doreturn = true;
					break;
				}
				break;
			}
			Move(playerpos, pointRight, mapdata);
			playerpos = pointRight;
			input = 0;
			int fchance = rand() % (20 - 1) + 1;
			if (fchance >= 5 && fchance <= 9) {
				encounter = spawnEnemy(sindex);
				if (encounter.name != "") {
					inFight = true;
					doreturn = true;
					break;
				}
			}
			break;
		}
		}
	}
//		POINT UP  ||  Position of Player
	if (playerpos == pointUp) {
		switch (input) {
		case 3:
		case 4:
		{
			ToPosition(width + 6, 10);
			cout << "Watch Out!!";
			Sleep(500);
			ToPosition(width + 6, 10);
			cout << "                               ";

			encounter = spawnEnemy(sindex);
			if (encounter.name != "") { 
				inFight = true;
				doreturn = true;
				break; 
			}
			//if the condition above is false then we dont do fight scene
			break;
		}
		case 2:
		{
			// Move Function
			Move(playerpos, centerPoint, mapdata);
			playerpos = centerPoint;
			int fchance = rand() % (20 - 1) + 1;
			if (fchance >= 5 && fchance <= 9) {
				encounter = spawnEnemy(sindex);
				if (encounter.name != "") {
					inFight = true;
					doreturn = true;
					break;
				}
			}
			break;
		}
		case 1:
			sindex = (sindex == 0) ? 1 : sindex;
			doreturn = true; //if true then the program knows that we changing  scene and break recursion before proceeding
			walkpast = Direction::up;
			break;
		}
	}
//		POINT DOWN  ||  Position of Player
	if (playerpos == pointDown) {
		switch (input) {
		case 1:
		{
			// Move Function
			Move(playerpos, centerPoint, mapdata);
			playerpos = centerPoint;
			int fchance = rand() % (20 - 1) + 1;
			if (fchance >= 5 && fchance <= 9) {
				encounter = spawnEnemy(sindex);
				if (encounter.name != "") {
					inFight = true;
					doreturn = true;
					break;
				}
			}
			break;
		}
		case 3:
		case 4:
		{
			ToPosition(width + 6, 10);
			cout << "Watch Out!!";
			Sleep(500);
			ToPosition(width + 6, 10);
			cout << "                               ";

			encounter = spawnEnemy(sindex);
			if (encounter.name != "") {
				inFight = true;
				doreturn = true;
				break;
			}
			break;
		}
		case 2:
			sindex = (sindex == 0) ? 2 : sindex;
			doreturn = true; //if true then the program knows that we changing  scene and break recursion before proceeding
			walkpast = Direction::down;
		}
	}

//		POINT LEFT  ||  Position of Player
	if (playerpos == pointLeft) {
		switch (input) {
		case 1:
		case 2:
		{
			ToPosition(width + 6, 10);
			cout << "Watch Out!!";
			Sleep(500);
			ToPosition(width + 6, 10);
			cout << "                               ";

			encounter = spawnEnemy(sindex);
			if (encounter.name != "") {
				inFight = true;
				doreturn = true;
				break;
			}
			break;
		}
		case 4:
		{
			// Move Function
			Move(playerpos, centerPoint, mapdata);
			playerpos = centerPoint;
			int fchance = rand() % (20 - 1) + 1;
			if (fchance >= 5 && fchance <= 9) {
				encounter = spawnEnemy(sindex);
				if (encounter.name != "") {
					inFight = true;
					doreturn = true;
					break;
				}
			}
			break;
		}
		case 3:
			doreturn = true; //if true then the program knows that we changing  scene and break recursion before proceeding
			walkpast = Direction::left;
			break;
		}
	}
//		POINT RIGHT  ||  Position of Player
	if (playerpos == pointRight) {
		switch (input) {
		case 1:
		case 2:
		{
			ToPosition(width + 6, 10);
			cout << "Watch Out!!";
			Sleep(500);
			ToPosition(width + 6, 10);
			cout << "                               ";

			encounter = spawnEnemy(sindex);
			if (encounter.name != "") {
				inFight = true;
				doreturn = true;
				break;
			}
			break;
		}
		case 3:
		{
			// Move Function
			Move(playerpos, centerPoint, mapdata);
			playerpos = centerPoint;
			int fchance = rand() % (20 - 1) + 1;
			if (fchance >= 5 && fchance <= 9) {
				encounter = spawnEnemy(sindex);
				if (encounter.name != "") {
					inFight = true;
					doreturn = true;
					break;
				}
			}
			break;
		}
		case 4:
			sindex = (sindex == 0) ? 3 : sindex;
			doreturn = true; //if true then the program knows that we changing  scene and break recursion before proceeding
			walkpast = Direction::right;
			break;
		}
	}
	return doreturn;
}


void pickMove(vector<vector<function<void()>>> scenes, Choices roads, Pos& playerpos, vector<vector<string>> mapData, map<Direction, int> scenenav) {

	bool interact = false;
	function<void(Player&, vector<vector<function<void()>>>)> talk;
	doRepeat = true;
	int indent = width + 6;
	int movepick = 0;
	bool changeScene;
	Direction pickedRoad;
//		D I S P L A Y    P L A Y E R
	if (inFight == false) {
		ToPosition(playerpos.x, playerpos.y);
		cout << playerID;
	}

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
	if (sindex == 0) {
		// show only option 5 at main scene
		ToPosition(indent, 6);
		cout << "5) Interact";
	}


	ToPosition(indent, 8);
	cout << "                      ";
	ToPosition(indent, 8);
	cout << "Choose an action : ";
	cin >> movepick;
	
	
	switch (movepick) {
	case 1:
		changeScene = canContinueMove(playerpos, roads, movepick, mapData, pickedRoad);
		// make dorepeat a parameter
		if (changeScene) {
			doRepeat = false;
		}
		break;
	case 2:
		changeScene = canContinueMove(playerpos, roads, movepick, mapData, pickedRoad);
		// make dorepeat a parameter
		if (changeScene) {
			doRepeat = false;
		}
		break;
	case 3:
		changeScene = canContinueMove(playerpos, roads, movepick, mapData, pickedRoad);
		// make dorepeat a parameter
		if (changeScene) {
			doRepeat = false;
		}
		break;
	case 4:
		changeScene = canContinueMove(playerpos, roads, movepick, mapData, pickedRoad);
		// make dorepeat a parameter
		if (changeScene) {
			doRepeat = false;
		}
		break;
	case 5:
		// interact npc  upgrade weapons and health  unlock weapons
		if (sindex != 0) { break; }

		ToPosition(indent, 2);
		cout << "                                   ";
		ToPosition(indent, 3);
		cout << "                                   ";
		ToPosition(indent, 4);
		cout << "                                   ";
		ToPosition(indent, 5);
		cout << "                                   ";
		ToPosition(indent, 6);
		cout << "                                   ";

		int i = 2;
		while (i <= 8) {
			ToPosition(indent, i);
			cout << "                         ";
			i++;
		}

		ToPosition(indent, 2);
		cout << "Interact to ???.";
		//  -------------------------------
		ToPosition(indent, 3);
		cout << "1) Guide";
		//  -------------------------------
		ToPosition(indent, 4);
		cout << "2) War Master";
		//  -------------------------------
		
		ToPosition(indent, 7);
		cout << "                           ";
		ToPosition(indent, 7);
		cout << "Your choice : ";

		int npc;
		cin >> npc;

		switch (npc) {
		case 1:
		{
			interact = true;
			doRepeat = false;
			talk = dispTuts;
			break;
		}
		case 2:
			interact = true;
			doRepeat = false;	
			talk = interactWarMaster;
		}

	}

	if (doRepeat) {
		return pickMove(scenes, roads, playerpos, mapData, scenenav);
	}else if (interact) {
		talk(player, scenes);
	}else if (inFight) {
		return startFight(player, encounter, scenes, playerpos);
	}
	else {
		playerpos = reversePosition[playerpos];
		if (scenenav[pickedRoad] == -1) {
			sindex = 0;
			sidx = 0;
			scenes[0][0]();
		}

		sidx = scenenav[pickedRoad];
		return scenes[sindex][scenenav[pickedRoad]]();
	}
	
}

#pragma endregion


#pragma region Map and Borders

/// <summary>
/// Draws border.
/// </summary>
/// <param name="height"></param>
/// <param name="width"></param>
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

/// <summary>
/// Draws custom lines and points in 4 direction 
/// </summary>
/// <param name="up"></param>
/// <param name="down"></param>
/// <param name="left"></param>
/// <param name="right"></param>
/// <returns></returns>
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

#pragma endregion
