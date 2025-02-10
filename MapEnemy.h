#pragma once
#include "BaseClass.h"
#include "definition.h"

class Map : public GameObject
{
public:
	Map();

	void Update() override;
	void Draw() override;
	void SetMap(int x, int i) const;

	static int mapCollision(Vector2 pos);

	Block map_[MAP_WIDTH][MAP_HEIGHT];
	static int mapBlock_[MAP_WIDTH][MAP_HEIGHT];

	int GameClearTime;
	int clearCount;

	int mapPttern[MAP_WIDTH][5] = {
	{ 1,2,2,1,2 },
	{ 1,1,2,1,3 },
	{ 1,1,2,1,2 },
	{ 1,1,1,1,1 },
	{ 1,1,2,1,1 },
	{ 2,1,2,2,2 },
	{ 2,1,2,1,2 },
	{ 1,1,1,1,2 },
	{ 1,1,2,3,1 },
	{ 1,1,2,1,1 },
	{ 1,1,2,2,2 },
	{ 1,2,1,1,2 },
	{ 1,2,2,1,2 },
	{ 1,1,2,1,1 },
	{ 1,1,2,2,1 },
	{ 1,1,1,1,2 },
	{ 1,1,3,1,2 },
	{ 2,1,2,1,2 },
	{ 2,1,2,1,1 },
	{ 1,1,1,2,1 },
	{ 1,1,2,1,2 },
	{ 1,1,2,1,2 },
	{ 1,1,2,1,2 },
	{ 1,2,1,1,1 },
	{ 1,2,2,1,1 },
	{ 1,1,2,2,2 },
	{ 1,1,2,1,2 },
	{ 1,3,1,1,2 },
	{ 1,1,2,1,1 },
	{ 2,1,2,1,1 },
	{ 2,1,2,2,2 },
	{ 1,1,1,1,2 },
	{ 1,1,2,1,2 },
	{ 1,1,2,1,1 },
	{ 1,1,2,2,1 },
	{ 1,2,1,1,2 },
	};


private:
	int frame;
};