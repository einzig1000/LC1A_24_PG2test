#pragma once
#include "Player.h"
#include "Camera.h"
#include "GetHitKey.h"
#include "definition.h"
#include "ChangeScene.h"
#include "MapEnemy.h"
#include "Count.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
public:
	// メンバ関数
	void Update();									// 更新処理
	void Draw();									// 描画処理
	void TitleUpdate();								// 更新処理(タイトル)
	void TitleDraw();								// 描画処理(タイトル)
	void GamePlayUpdate();							// 更新処理(ゲームプレイ)
	void GamePlayDraw();							// 描画処理(ゲームプレイ)
	void ResultUpdate();							// 更新処理(リザルト)
	void ResultDraw();								// 描画処理(リザルト)
	void GetScreenPos();							// 座標変換

	static Scene scene;
	static int MainFrame_;
	static int Score_;

private:
	GetHitKey* getHitkey = new GetHitKey();
	Player* player = new Player();
	Camera* camera = new Camera();
	Map* map = new Map();
	ChangeScene* CS = new ChangeScene();
	Count* countPrint = new Count();

	Vector2 WorldBorder[2][2];
	Vector2 DrawWorldBorder[2][2];
	int magicNum;
};

