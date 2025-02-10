#include "Player.h"
#include "MapEnemy.h"
#include "GameManager.h"

Player::Player()
{
	size_ = { 8,8 };
	//pos_ = { WINDOW_WIDTH / 2.0f,WINDOW_WIDTH / 2.0f };
	pos_ = { 150,80 };
	vertex_.LT = { pos_.x - size_.x,pos_.y - size_.y };
	vertex_.RT = { pos_.x + size_.x,pos_.y - size_.y };
	vertex_.LB = { pos_.x - size_.x,pos_.y + size_.y };
	vertex_.RB = { pos_.x + size_.x,pos_.y + size_.y };
	vel_ = { 0,0 };
	acc_ = { 0,0 };
	ObjectID = ID_Player;

	R_ = 0x60;
	G_ = 0x60;
	B_ = 0x00;

	preShotCoolTime_ = 0;

	Direction_ = 0;

	for (int i = 0; i < BulletSum; ++i)
	{
		bullet[i] = new Bullet;
	}

	AliveArea.LT = { 50,700 };
	AliveArea.LB = { 50,0 };
	AliveArea.RT = { 199,700 };
	AliveArea.RB = { 199,0 };
	GameOverTime = 0;
}

Player::~Player()
{
	for (int i = 0; i < BulletSum; ++i)
	{
		delete bullet[i];
	}
}

void Player::Update()
{
	// Bullet処理
	if (GetHitKey::keys[DIK_SPACE] && preShotCoolTime_ <= 0)
	{
		for (int i = 0; i < BulletSum; ++i)
		{
			if (bullet[i]->GetIsShot() == 0)
			{
				bullet[i]->SetIsShot(1);
				bullet[i]->SetPos(pos_);
				preShotCoolTime_ = 5;
				break;
			}
		}
	}
	if (preShotCoolTime_ > 0)
	{
		preShotCoolTime_--;
	}
	for (int i = 0; i < BulletSum; ++i)
	{
		if (bullet[i]->GetIsShot() == 1)
		{
			bullet[i]->Update(Direction_);
		}
	}


	// 速度を直接変更
	vel_ = { 0,0 };
	if (GetHitKey::keys[DIK_W] && GetHitKey::keys[DIK_A])
	{
		vel_.y += 3.5f;
		vel_.x -= 3.5f;
		Direction_ = LT;
	}
	else if (GetHitKey::keys[DIK_W] && GetHitKey::keys[DIK_D])
	{
		vel_.y += 3.5f;
		vel_.x += 3.5f;
		Direction_ = RT;
	}
	else if (GetHitKey::keys[DIK_S] && GetHitKey::keys[DIK_A])
	{
		vel_.y -= 3.5f;
		vel_.x -= 3.5f;
		Direction_ = LB;
	}
	else if (GetHitKey::keys[DIK_S] && GetHitKey::keys[DIK_D])
	{
		vel_.y -= 3.5f;
		vel_.x += 3.5f;
		Direction_ = RB;
	}
	else if (GetHitKey::keys[DIK_W])
	{
		vel_.y += 5;
		Direction_ = Top;
	}
	else if (GetHitKey::keys[DIK_S])
	{
		vel_.y -= 5;
		Direction_ = Bottom;
	}
	else if (GetHitKey::keys[DIK_D])
	{
		vel_.x += 5;
		Direction_ = Right;
	}
	else if (GetHitKey::keys[DIK_A])
	{
		vel_.x -= 5;
		Direction_ = Left;
	}

	if (GetHitKey::keys[DIK_LSHIFT] || GetHitKey::keys[DIK_RSHIFT])
	{
		Direction_ = Right;
	}


	// 速度の絶対値を取得　(abs(vel_)を何度も呼び出さないようにするため)
	absVel_.x = abs(vel_.x);
	absVel_.y = abs(vel_.y);


	// 移動
	/// 自信の移動によるめり込み回避
	for (int MoveUnit = 0; MoveUnit < absVel_.x; MoveUnit += 1)
	{
		if (vel_.x > 0 && pos_.x < AliveArea.RB.x - size_.x)
		{
			if (
				// 右上が当たってない 
				Map::mapCollision({ pos_.x + size_.x,pos_.y + size_.y }) == 0 &&
				// 右下が当たってない
				Map::mapCollision({ pos_.x + size_.x,pos_.y - size_.y }) == 0)
			{
				pos_.x += 1;

				if (
					// 移動した結果右上が当たった 
					Map::mapCollision({ pos_.x + size_.x,pos_.y + size_.y }) != 0 ||
					// 移動した結果右下が当たった 
					Map::mapCollision({ pos_.x + size_.x,pos_.y - size_.y }) != 0)
				{
					pos_.x -= 1;
				}
			}
		}
		else if (vel_.x < 0 && pos_.x > AliveArea.LB.x + size_.x)
		{
			if (
				// 左上が当たってない 
				Map::mapCollision({ pos_.x - size_.x,pos_.y + size_.y }) == 0 &&
				// 左下が当たってない
				Map::mapCollision({ pos_.x - size_.x,pos_.y - size_.y }) == 0)
			{
				pos_.x -= 1;

				if (
					// 移動した結果左上が当たった 
					Map::mapCollision({ pos_.x - size_.x,pos_.y + size_.y }) != 0 ||
					// 移動した結果左下が当たった 
					Map::mapCollision({ pos_.x - size_.x,pos_.y - size_.y }) != 0)
				{
					pos_.x += 1;
				}
			}
		}
	}
	for (int MoveUnit = 0; MoveUnit < absVel_.y; MoveUnit += 1)
	{
		if (vel_.y > 0 && pos_.y < AliveArea.LT.y - size_.y)
		{
			if (
				// 右上が当たってない 
				Map::mapCollision({ pos_.x + size_.x,pos_.y + size_.y }) == 0 &&
				// 左上が当たってない
				Map::mapCollision({ pos_.x - size_.x,pos_.y + size_.y }) == 0)
			{
				pos_.y += 1;

				if (
					// 移動した結果右上が当たった 
					Map::mapCollision({ pos_.x + size_.x,pos_.y + size_.y }) != 0 ||
					// 移動した結果左上が当たった 
					Map::mapCollision({ pos_.x - size_.x,pos_.y + size_.y }) != 0)
				{
					pos_.y -= 1;
				}
			}
		}
		else if (vel_.y < 0 && pos_.y > AliveArea.LB.y + size_.y)
		{
			if (
				// 右下が当たってない 
				Map::mapCollision({ pos_.x + size_.x,pos_.y - size_.y }) == 0 &&
				// 左下が当たってない
				Map::mapCollision({ pos_.x - size_.x,pos_.y - size_.y }) == 0)
			{
				pos_.y -= 1;


				if (
					// 移動した結果右下が当たった 
					Map::mapCollision({ pos_.x + size_.x,pos_.y - size_.y }) != 0 ||
					// 移動した結果左下が当たった 
					Map::mapCollision({ pos_.x - size_.x,pos_.y - size_.y }) != 0)
				{
					pos_.y += 1;
				}
			}
		}
	}

	/// 環境の移動によるめり込み回避
	while (
		// 移動した結果右上が当たった 
		Map::mapCollision({ pos_.x + size_.x,pos_.y + size_.y }) != 0 ||
		// 移動した結果右下が当たった 
		Map::mapCollision({ pos_.x + size_.x,pos_.y - size_.y }) != 0 ||
		// 移動した結果左上が当たった 
		Map::mapCollision({ pos_.x - size_.x,pos_.y + size_.y }) != 0 ||
		// 移動した結果左下が当たった 
		Map::mapCollision({ pos_.x - size_.x,pos_.y - size_.y }) != 0)
	{
		pos_.x -= 1;
	}

	// 生存エリアからでたら死ぬ
	if (vertex_.LT.x < AliveArea.LT.x)
	{
		GameOverTime = GameManager::MainFrame_;
	}


	// posから四隅
	vertex_.LT = { pos_.x - size_.x,pos_.y - size_.y };
	vertex_.RT = { pos_.x + size_.x,pos_.y - size_.y };
	vertex_.LB = { pos_.x - size_.x,pos_.y + size_.y };
	vertex_.RB = { pos_.x + size_.x,pos_.y + size_.y };


	Camera();
}

void Player::Draw()
{
	Novice::DrawQuad(
		int(DrawAliveArea.LB.x), int(DrawAliveArea.LB.y),
		int(DrawAliveArea.RB.x), int(DrawAliveArea.RB.y),
		int(DrawAliveArea.LT.x), int(DrawAliveArea.LT.y),
		int(DrawAliveArea.RT.x), int(DrawAliveArea.RT.y),
		0, 0, 1, 1, white1x1,
		0xFF000055
	);



	for (int i = 0; i < BulletSum; ++i)
	{
		if (bullet[i]->GetIsShot() == 1)
		{
			bullet[i]->Draw();
		}
	}
	Novice::DrawQuad(
		int(drawvertex_.LB.x), int(drawvertex_.LB.y),
		int(drawvertex_.RB.x), int(drawvertex_.RB.y),
		int(drawvertex_.LT.x), int(drawvertex_.LT.y),
		int(drawvertex_.RT.x), int(drawvertex_.RT.y),
		0, 0, 1, 1, white1x1,
		GetColor()
	);

	if (Direction_ == Left)
	{
		Novice::DrawLine(int(drawpos_.x), int(drawpos_.y), int(drawpos_.x - 50), int(drawpos_.y), RED);
		Novice::DrawLine(int(drawpos_.x), int(drawpos_.y), int(drawpos_.x), int(drawpos_.y - 50), BLUE);
	}
	else if (Direction_ == Right)
	{
		Novice::DrawLine(int(drawpos_.x), int(drawpos_.y), int(drawpos_.x + 50), int(drawpos_.y), RED);
		Novice::DrawLine(int(drawpos_.x), int(drawpos_.y), int(drawpos_.x), int(drawpos_.y + 50), BLUE);
	}
	else if (Direction_ == Top)
	{
		Novice::DrawLine(int(drawpos_.x), int(drawpos_.y), int(drawpos_.x), int(drawpos_.y - 50), RED);
		Novice::DrawLine(int(drawpos_.x), int(drawpos_.y), int(drawpos_.x + 50), int(drawpos_.y), BLUE);
	}
	else if (Direction_ == Bottom)
	{
		Novice::DrawLine(int(drawpos_.x), int(drawpos_.y), int(drawpos_.x), int(drawpos_.y + 50), RED);
		Novice::DrawLine(int(drawpos_.x), int(drawpos_.y), int(drawpos_.x - 50), int(drawpos_.y), BLUE);
	}
	else if (Direction_ == LT)
	{
		Novice::DrawLine(int(drawpos_.x), int(drawpos_.y), int(drawpos_.x - 35), int(drawpos_.y - 35), RED);
		Novice::DrawLine(int(drawpos_.x), int(drawpos_.y), int(drawpos_.x + 35), int(drawpos_.y - 35), BLUE);
	}
	else if (Direction_ == RT)
	{
		Novice::DrawLine(int(drawpos_.x), int(drawpos_.y), int(drawpos_.x + 35), int(drawpos_.y - 35), RED);
		Novice::DrawLine(int(drawpos_.x), int(drawpos_.y), int(drawpos_.x + 35), int(drawpos_.y + 35), BLUE);
	}
	else if (Direction_ == RB)
	{
		Novice::DrawLine(int(drawpos_.x), int(drawpos_.y), int(drawpos_.x + 35), int(drawpos_.y + 35), RED);
		Novice::DrawLine(int(drawpos_.x), int(drawpos_.y), int(drawpos_.x - 35), int(drawpos_.y + 35), BLUE);
	}
	else if (Direction_ == LB)
	{
		Novice::DrawLine(int(drawpos_.x), int(drawpos_.y), int(drawpos_.x - 35), int(drawpos_.y + 35), RED);
		Novice::DrawLine(int(drawpos_.x), int(drawpos_.y), int(drawpos_.x - 35), int(drawpos_.y - 35), BLUE);
	}


	Novice::ScreenPrintf(int(drawvertex_.LB.x), int(drawvertex_.LB.y), "%d", GameManager::Score_);
}
