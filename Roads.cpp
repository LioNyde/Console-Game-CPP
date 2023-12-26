#include <iostream>
#include <vector>

#include "Classes.h"

using namespace std;

vector<Road> Scene1 = {
	{Direction::up, 0, "Scene1"},
	{Direction::down, 2, "Scene1"},
	{Direction::left, 1, "Scene1"}
};

vector<Road> SceneA1 = {
	{Direction::down, 0, "SceneA1"},
	{Direction::right, 1, "SceneA1"}
};

vector<Road> SceneA2 = {
	{Direction::left, 1, "SceneB1"},
	{Direction::right, 2, "SceneB1"}
};

vector<Road> SceneA3 = {
	{Direction::up, 3, "SceneA3"},
	{Direction::left, 2, "SceneA3"}
};

vector<Road> SceneA4 = {
	{Direction::down, 1, "SceneA4"},
};

