#pragma once
#include "BaseClass.h"
#include <cmath> // abs関数を使用するために必要
#include "Bullet.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	void Update() override;
	void Draw() override;

	Vertex AliveArea;
	Vertex DrawAliveArea;
	int GameOverTime;

private:
	int Direction_;
	int preShotCoolTime_;
	Bullet* bullet[BulletSum];
};