#include "GameManager.h"

Scene GameManager::scene;
int GameManager::MainFrame_;
int GameManager::Score_;

GameManager::GameManager()
{
	scene = TITLE;
	MainFrame_ = 0;
	magicNum = 0;
	Score_ = 0;
	WorldBorder[0][0] = { -300,0 };
	WorldBorder[0][1] = { 3000,0 };
	WorldBorder[1][0] = { 0,-300 };
	WorldBorder[1][1] = { 0,3000 };
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			DrawWorldBorder[i][j] = { 0,0 };
		}
	}
}

GameManager::~GameManager()
{
	delete getHitkey;
	delete player;
	delete camera;
	delete map;
	delete CS;
	delete countPrint;
}

/*///////////////////////////////////////
				メイン
///////////////////////////////////////*/
void GameManager::Update()
{
	getHitkey->Update();
	if (scene == TITLE)
	{
		TitleUpdate();
	}
	else if (scene == GAME_PLAY)
	{
		GamePlayUpdate();
	}
	else if (scene == RESULT)
	{
		ResultUpdate();
	}
	// カメラ関係
	camera->Update(player);
	GameManager::GetScreenPos();
	// メインフレーム更新
	MainFrame_++;
}
void GameManager::Draw()
{
	Novice::DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0x34ff57FF, kFillModeSolid);
	Novice::DrawLine(int(DrawWorldBorder[0][0].x), int(DrawWorldBorder[0][0].y), int(DrawWorldBorder[0][1].x), int(DrawWorldBorder[0][1].y), RED);
	Novice::DrawLine(int(DrawWorldBorder[1][0].x), int(DrawWorldBorder[1][0].y), int(DrawWorldBorder[1][1].x), int(DrawWorldBorder[1][1].y), BLUE);
	if (scene == TITLE)
	{
		TitleDraw();
	}
	else if (scene == GAME_PLAY)
	{
		GamePlayDraw();
	}
	else if (scene == RESULT)
	{
		ResultDraw();
	}
}

/*///////////////////////////////////////
			　　タイトル
///////////////////////////////////////*/
void GameManager::TitleUpdate()
{
	if (GetHitKey::keys[DIK_SPACE] && !GetHitKey::preKeys[DIK_SPACE])
	{
		scene = GAME_PLAY;
		MainFrame_ = 0;
		player->Update();
		map->Update();
	}
}
void GameManager::TitleDraw()
{
	Novice::ScreenPrintf(110, 300, "Press Space to start.");
}

/*///////////////////////////////////////
			　プレイシーン
///////////////////////////////////////*/
void GameManager::GamePlayUpdate()
{
	if (MainFrame_ > 240)
	{
		if (player->GameOverTime == 0 && map->GameClearTime == 0)
		{
			player->Update();
			map->Update();
		}
		else
		{
			if (player->GameOverTime != 0)
			{
				CS->stages2(MainFrame_ - player->GameOverTime, 60, 20, 40, 5, player->GetDrawpos(), WINDOW_WIDTH, 50, 0);
				if (MainFrame_ - player->GameOverTime >= 180)
				{
					CS->stages2(magicNum, 60, 0, 0, 60, { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 }, 0, WINDOW_WIDTH, WINDOW_WIDTH);
					magicNum++;
					Novice::DrawBox(100, 290, 280, 40, 0, BLACK, kFillModeSolid);
					Novice::ScreenPrintf(110, 300, "Press R to restart.");
				}
			}
			if (map->GameClearTime != 0)
			{
				CS->stages2(MainFrame_ - map->GameClearTime, 60, 20, 40, 5, player->GetDrawpos(), WINDOW_WIDTH, 50, 0);
				if (MainFrame_ - map->GameClearTime >= 180)
				{
					CS->stages2(magicNum, 60, 0, 0, 60, { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 }, 0, WINDOW_WIDTH, WINDOW_WIDTH);
					magicNum++;
				}
				if (MainFrame_ - map->GameClearTime >= 240)
				{
					scene = RESULT;
				}
			}
		}
	}
	else
	{
		countPrint->Update(3, 0, { 300,600 }, { 5,5 });
	}

}
void GameManager::GamePlayDraw()
{
	if (magicNum == 0)
	{
		map->Draw();
		player->Draw();
	}
	if ((player->GameOverTime != 0 || map->GameClearTime != 0) && magicNum < 60)
	{
		CS->Draw();
	}
	if (MainFrame_ < 240)
	{
		countPrint->Draw();
	}
}

/*///////////////////////////////////////
		　　リザルトシーン
///////////////////////////////////////*/
void GameManager::ResultUpdate()
{

}
void GameManager::ResultDraw()
{
	Novice::DrawBox(190, 350, 100, 40, 0, BLACK, kFillModeSolid);
	Novice::ScreenPrintf(200, 360, "SCORE:%d", Score_);
	Novice::DrawBox(100, 290, 280, 40, 0, BLACK, kFillModeSolid);
	Novice::ScreenPrintf(110, 300, "Press Space to restart.");
}



/*///////////////////////////////////////
			　　座標変換				
///////////////////////////////////////*/
void GameManager::GetScreenPos()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			DrawWorldBorder[i][j] = camera->Transform(WorldBorder[i][j], camera->wvpVpMatrix);
		}
	}
	for (int x = 0; x < MAP_HEIGHT; ++x)
	{
		for (int y = 0; y < MAP_WIDTH; ++y)
		{
			map->map_[y][x].drawvertex_.LT = camera->Transform(map->map_[y][x].vertexPos.LT, camera->wvpVpMatrix);
			map->map_[y][x].drawvertex_.RT = camera->Transform(map->map_[y][x].vertexPos.RT, camera->wvpVpMatrix);
			map->map_[y][x].drawvertex_.LB = camera->Transform(map->map_[y][x].vertexPos.LB, camera->wvpVpMatrix);
			map->map_[y][x].drawvertex_.RB = camera->Transform(map->map_[y][x].vertexPos.RB, camera->wvpVpMatrix);
		}
	}

	player->DrawAliveArea.LT = camera->Transform(player->AliveArea.LT, camera->wvpVpMatrix);
	player->DrawAliveArea.RT = camera->Transform(player->AliveArea.RT, camera->wvpVpMatrix);
	player->DrawAliveArea.LB = camera->Transform(player->AliveArea.LB, camera->wvpVpMatrix);
	player->DrawAliveArea.RB = camera->Transform(player->AliveArea.RB, camera->wvpVpMatrix);
}