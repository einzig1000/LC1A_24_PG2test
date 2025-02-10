#include "MapEnemy.h"
#include "GameManager.h"

int Map::mapBlock_[MAP_WIDTH][MAP_HEIGHT];

Map::Map()
{
	for (int x = 0; x < MAP_HEIGHT; ++x)
	{
		for (int y = 0; y < MAP_WIDTH; ++y)
		{
			map_[y][x].pos = { (BLOCKSIZE / 2.0f) + (BLOCKSIZE * x), (BLOCKSIZE / 2.0f) + (BLOCKSIZE * y) };
			map_[y][x].vertexPos.LT = { map_[y][x].pos.x - (BLOCKSIZE / 2.0f), map_[y][x].pos.y + (BLOCKSIZE / 2.0f) };
			map_[y][x].vertexPos.RT = { map_[y][x].pos.x + (BLOCKSIZE / 2.0f), map_[y][x].pos.y + (BLOCKSIZE / 2.0f) };
			map_[y][x].vertexPos.LB = { map_[y][x].pos.x - (BLOCKSIZE / 2.0f), map_[y][x].pos.y - (BLOCKSIZE / 2.0f) };
			map_[y][x].vertexPos.RB = { map_[y][x].pos.x + (BLOCKSIZE / 2.0f), map_[y][x].pos.y - (BLOCKSIZE / 2.0f) };
		}
	}


	for (int x = 0; x < MAP_HEIGHT; ++x)
	{
		for (int y = 0; y < MAP_WIDTH; ++y)
		{
			mapBlock_[y][x] = 0;
		}
	}

	GameClearTime = 0;
	clearCount = 0;


	for (int y = 0; y < MAP_HEIGHT; ++y)
	{
		if (y % 5 == 0)
		{
			SetMap(y, rand() % 5);
		}
	}

	frame = 1;
}

void Map::Update()
{
	if (frame % 10 == 0)
	{
		for (int x = 1; x < MAP_HEIGHT; ++x)
		{
			for (int y = 0; y < MAP_WIDTH; ++y)
			{
				mapBlock_[y][x - 1] = mapBlock_[y][x];
			}
		}
		for (int x = 0; x < MAP_HEIGHT; ++x)
		{
			for (int y = 0; y < MAP_WIDTH; ++y)
			{
				if (mapBlock_[y][x] == 0)
				{
					clearCount++;
					if (clearCount >= (MAP_WIDTH - 1) * (MAP_HEIGHT - 1))
					GameClearTime = GameManager::MainFrame_;
				}
				else
				{
					clearCount = 0;
					x = MAP_HEIGHT;
					break;
				}
			}
		}
	}

	Camera();
	frame++;
}

void Map::Draw()
{
	for (int x = 0; x < MAP_HEIGHT; ++x)
	{
		for (int y = 0; y < MAP_WIDTH; ++y)
		{
			if (mapBlock_[y][x] == Normal)
			{
				if (map_[y][x].drawvertex_.LT.x > 0 && map_[y][x].drawvertex_.LT.y < 720 &&
					map_[y][x].drawvertex_.RB.x < 1280 && map_[y][x].drawvertex_.RB.x > 0)
				{
					Novice::DrawQuad(
						int(map_[y][x].drawvertex_.LT.x), int(map_[y][x].drawvertex_.LT.y),
						int(map_[y][x].drawvertex_.RT.x), int(map_[y][x].drawvertex_.RT.y),
						int(map_[y][x].drawvertex_.LB.x), int(map_[y][x].drawvertex_.LB.y),
						int(map_[y][x].drawvertex_.RB.x), int(map_[y][x].drawvertex_.RB.y),
						0, 0, 1, 1,
						white1x1, 0x575652FF
					);
					Novice::DrawLine(
						int(map_[y][x].drawvertex_.LT.x), int(map_[y][x].drawvertex_.LT.y),
						int(map_[y][x].drawvertex_.RT.x), int(map_[y][x].drawvertex_.RT.y),
						BLACK);
					Novice::DrawLine(
						int(map_[y][x].drawvertex_.RT.x), int(map_[y][x].drawvertex_.RT.y),
						int(map_[y][x].drawvertex_.RB.x), int(map_[y][x].drawvertex_.RB.y),
						BLACK);
					Novice::DrawLine(
						int(map_[y][x].drawvertex_.RB.x), int(map_[y][x].drawvertex_.RB.y),
						int(map_[y][x].drawvertex_.LB.x), int(map_[y][x].drawvertex_.LB.y),
						BLACK);
					Novice::DrawLine(
						int(map_[y][x].drawvertex_.LB.x), int(map_[y][x].drawvertex_.LB.y),
						int(map_[y][x].drawvertex_.LT.x), int(map_[y][x].drawvertex_.LT.y),
						BLACK);

				}
			}
			else if (mapBlock_[y][x] == Enemy)
			{
				if (map_[y][x].drawvertex_.LT.x > 0 && map_[y][x].drawvertex_.LT.y < 720 &&
					map_[y][x].drawvertex_.RB.x < 1280 && map_[y][x].drawvertex_.RB.x > 0)
				{
					Novice::DrawQuad(
						int(map_[y][x].drawvertex_.LT.x), int(map_[y][x].drawvertex_.LT.y),
						int(map_[y][x].drawvertex_.RT.x), int(map_[y][x].drawvertex_.RT.y),
						int(map_[y][x].drawvertex_.LB.x), int(map_[y][x].drawvertex_.LB.y),
						int(map_[y][x].drawvertex_.RB.x), int(map_[y][x].drawvertex_.RB.y),
						0, 0, 1, 1,
						white1x1, 0xe62b2bFF
					);
					Novice::DrawQuad(
						int(map_[y][x].drawvertex_.LT.x + (BLOCKSIZE / 2.0f)), int(map_[y][x].drawvertex_.LT.y),
						int(map_[y][x].drawvertex_.RT.x), int(map_[y][x].drawvertex_.RT.y + (BLOCKSIZE / 2.0f)),
						int(map_[y][x].drawvertex_.LB.x), int(map_[y][x].drawvertex_.LB.y - (BLOCKSIZE / 2.0f)),
						int(map_[y][x].drawvertex_.RB.x - (BLOCKSIZE / 2.0f)), int(map_[y][x].drawvertex_.RB.y),
						0, 0, 1, 1,
						white1x1, BLACK
					);
					Novice::DrawQuad(
						int(map_[y][x].drawvertex_.LT.x + (BLOCKSIZE / 7.0f)), int(map_[y][x].drawvertex_.LT.y + (BLOCKSIZE / 7.0f)),
						int(map_[y][x].drawvertex_.RT.x - (BLOCKSIZE / 7.0f)), int(map_[y][x].drawvertex_.RT.y + (BLOCKSIZE / 7.0f)),
						int(map_[y][x].drawvertex_.LB.x + (BLOCKSIZE / 7.0f)), int(map_[y][x].drawvertex_.LB.y - (BLOCKSIZE / 7.0f)),
						int(map_[y][x].drawvertex_.RB.x - (BLOCKSIZE / 7.0f)), int(map_[y][x].drawvertex_.RB.y - (BLOCKSIZE / 7.0f)),
						0, 0, 1, 1,
						white1x1, BLACK
					);
					Novice::DrawLine(
						int(map_[y][x].drawvertex_.LT.x), int(map_[y][x].drawvertex_.LT.y),
						int(map_[y][x].drawvertex_.RT.x), int(map_[y][x].drawvertex_.RT.y),
						BLACK);
					Novice::DrawLine(
						int(map_[y][x].drawvertex_.RT.x), int(map_[y][x].drawvertex_.RT.y),
						int(map_[y][x].drawvertex_.RB.x), int(map_[y][x].drawvertex_.RB.y),
						BLACK);
					Novice::DrawLine(
						int(map_[y][x].drawvertex_.RB.x), int(map_[y][x].drawvertex_.RB.y),
						int(map_[y][x].drawvertex_.LB.x), int(map_[y][x].drawvertex_.LB.y),
						BLACK);
					Novice::DrawLine(
						int(map_[y][x].drawvertex_.LB.x), int(map_[y][x].drawvertex_.LB.y),
						int(map_[y][x].drawvertex_.LT.x), int(map_[y][x].drawvertex_.LT.y),
						BLACK);
				}
			}
			else if (mapBlock_[y][x] == Point)
			{
				if (map_[y][x].drawvertex_.LT.x > 0 && map_[y][x].drawvertex_.LT.y < 720 &&
					map_[y][x].drawvertex_.RB.x < 1280 && map_[y][x].drawvertex_.RB.x > 0)
				{
					Novice::DrawQuad(
						int(map_[y][x].drawvertex_.LT.x), int(map_[y][x].drawvertex_.LT.y),
						int(map_[y][x].drawvertex_.RT.x), int(map_[y][x].drawvertex_.RT.y),
						int(map_[y][x].drawvertex_.LB.x), int(map_[y][x].drawvertex_.LB.y),
						int(map_[y][x].drawvertex_.RB.x), int(map_[y][x].drawvertex_.RB.y),
						0, 0, 1, 1,
						white1x1, WHITE
					);
					Novice::DrawQuad(
						int(map_[y][x].drawvertex_.LT.x + (BLOCKSIZE / 2.0f)), int(map_[y][x].drawvertex_.LT.y),
						int(map_[y][x].drawvertex_.RT.x), int(map_[y][x].drawvertex_.RT.y + (BLOCKSIZE / 2.0f)),
						int(map_[y][x].drawvertex_.LB.x), int(map_[y][x].drawvertex_.LB.y - (BLOCKSIZE / 2.0f)),
						int(map_[y][x].drawvertex_.RB.x - (BLOCKSIZE / 2.0f)), int(map_[y][x].drawvertex_.RB.y),
						0, 0, 1, 1,
						white1x1, 0xaca400FF
					);
					Novice::DrawQuad(
						int(map_[y][x].drawvertex_.LT.x + (BLOCKSIZE / 7.0f)), int(map_[y][x].drawvertex_.LT.y + (BLOCKSIZE / 7.0f)),
						int(map_[y][x].drawvertex_.RT.x - (BLOCKSIZE / 7.0f)), int(map_[y][x].drawvertex_.RT.y + (BLOCKSIZE / 7.0f)),
						int(map_[y][x].drawvertex_.LB.x + (BLOCKSIZE / 7.0f)), int(map_[y][x].drawvertex_.LB.y - (BLOCKSIZE / 7.0f)),
						int(map_[y][x].drawvertex_.RB.x - (BLOCKSIZE / 7.0f)), int(map_[y][x].drawvertex_.RB.y - (BLOCKSIZE / 7.0f)),
						0, 0, 1, 1,
						white1x1, 0xaca400FF
					);
					Novice::DrawLine(
						int(map_[y][x].drawvertex_.LT.x), int(map_[y][x].drawvertex_.LT.y),
						int(map_[y][x].drawvertex_.RT.x), int(map_[y][x].drawvertex_.RT.y),
						BLACK);
					Novice::DrawLine(
						int(map_[y][x].drawvertex_.RT.x), int(map_[y][x].drawvertex_.RT.y),
						int(map_[y][x].drawvertex_.RB.x), int(map_[y][x].drawvertex_.RB.y),
						BLACK);
					Novice::DrawLine(
						int(map_[y][x].drawvertex_.RB.x), int(map_[y][x].drawvertex_.RB.y),
						int(map_[y][x].drawvertex_.LB.x), int(map_[y][x].drawvertex_.LB.y),
						BLACK);
					Novice::DrawLine(
						int(map_[y][x].drawvertex_.LB.x), int(map_[y][x].drawvertex_.LB.y),
						int(map_[y][x].drawvertex_.LT.x), int(map_[y][x].drawvertex_.LT.y),
						BLACK);
				}
			}
		}
	}
}

void Map::SetMap(int x, int i) const
{
	for (int y = 0; y < MAP_WIDTH; ++y)
	{
		mapBlock_[y][x] = mapPttern[y][i];
	}
}

int Map::mapCollision(Vector2 pos)
{
	// マップと衝突してなかったら０
	if (mapBlock_[int(pos.y) / BLOCKSIZE][int(pos.x) / BLOCKSIZE] == Air)
	{
		return Air;
	}
	// マップと衝突してたら１
	else if (mapBlock_[int(pos.y) / BLOCKSIZE][int(pos.x) / BLOCKSIZE] == Normal)
	{
		return Normal;
	}
	// 敵と衝突してたら2
	else if (mapBlock_[int(pos.y) / BLOCKSIZE][int(pos.x) / BLOCKSIZE] == Enemy)
	{
		return Enemy;
	}
	// 敵と衝突してたら3
	else if (mapBlock_[int(pos.y) / BLOCKSIZE][int(pos.x) / BLOCKSIZE] == Point)
	{
		return Point;
	}
	else return 100;
}