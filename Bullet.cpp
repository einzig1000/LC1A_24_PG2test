#include "Bullet.h"
#include "MapEnemy.h"
#include "GameManager.h"

Bullet::Bullet()
{
	isShot_ = 0;
	InitializeFlag_ = 0;
	Direction_ = 0;
	size_ = { 4,4 };

	R_ = 0xFF;
	G_ = 0xFF;
	B_ = 0x00;
}

void Bullet::Update(int direction)
{
	if (InitializeFlag_ == 0)
	{
		Direction_ = direction;
		InitializeFlag_ = 1;
	}

	if (Direction_ == Left)
	{
		vel_.x = -7.5f;
		vel_.y = 0;
	}
	else if (Direction_ == Right)
	{
		vel_.x = 7.5f;
		vel_.y = 0;
	}
	else if (Direction_ == Top)
	{
		vel_.y = 7.5f;
		vel_.x = 0;
	}
	else if (Direction_ == Bottom)
	{
		vel_.y = -7.5f;
		vel_.x = 0;
	}
	else if (Direction_ == LT)
	{
		vel_.y = 5.25f;
		vel_.x = -5.25f;
	}
	else if (Direction_ == LB)
	{
		vel_.y = -5.25f;
		vel_.x = -5.25f;
	}
	else if (Direction_ == RT)
	{
		vel_.y = 5.25f;
		vel_.x = 5.25f;
	}
	else if (Direction_ == RB)
	{
		vel_.y = -5.25f;
		vel_.x = 5.25f;
	}



	// 速度の絶対値を取得　(abs(vel_)を何度も呼び出さないようにするため)
	absVel_.x = abs(vel_.x);
	absVel_.y = abs(vel_.y);


	// 移動
	for (int MoveUnit = 0; MoveUnit < absVel_.x; MoveUnit += 1)
	{
		if (vel_.x > 0)
		{
			if (
				// 右上が当たってない 
				Map::mapCollision({ pos_.x + size_.x,pos_.y + size_.y }) == 0 &&
				// 右下が当たってない
				Map::mapCollision({ pos_.x + size_.x,pos_.y - size_.y }) == 0)
			{
				pos_.x += 1;
				CollisionCheck();
			}
		}
		else if (vel_.x < 0)
		{
			if (
				// 左上が当たってない 
				Map::mapCollision({ pos_.x - size_.x,pos_.y + size_.y }) == 0 &&
				// 左下が当たってない
				Map::mapCollision({ pos_.x - size_.x,pos_.y - size_.y }) == 0)
			{
				pos_.x -= 1;
				CollisionCheck();
			}
		}
	}
	for (int MoveUnit = 0; MoveUnit < absVel_.y; MoveUnit += 1)
	{
		if (vel_.y > 0)
		{
			if (
				// 右上が当たってない 
				Map::mapCollision({ pos_.x + size_.x,pos_.y + size_.y }) == 0 &&
				// 左上が当たってない
				Map::mapCollision({ pos_.x - size_.x,pos_.y + size_.y }) == 0)
			{
				pos_.y += 1;
				CollisionCheck();
			}
		}
		else if (vel_.y < 0)
		{
			if (
				// 右下が当たってない 
				Map::mapCollision({ pos_.x + size_.x,pos_.y - size_.y }) == 0 &&
				// 左下が当たってない
				Map::mapCollision({ pos_.x - size_.x,pos_.y - size_.y }) == 0)
			{
				pos_.y -= 1;
				CollisionCheck();
			}
		}
	}

	CollisionCheck();
	Camera();
}

void Bullet::Draw()
{
	if (isShot_ == 1)Novice::DrawEllipse(int(drawpos_.x), int(drawpos_.y), int(size_.x), int(size_.y), 0, GetColor(), kFillModeSolid);
}

void Bullet::CollisionCheck()
{
	// 敵に当たった  
	if (Map::mapCollision({ pos_.x + size_.x,pos_.y + size_.y }) == Enemy)
	{
		Map::mapBlock_[int(pos_.y + size_.y) / BLOCKSIZE][int(pos_.x + size_.x) / BLOCKSIZE] = Air;
		isShot_ = 0;
		InitializeFlag_ = 0;
	}
	// 敵に当たった  
	if (Map::mapCollision({ pos_.x + size_.x,pos_.y - size_.y }) == Enemy)
	{
		Map::mapBlock_[int(pos_.y - size_.y) / BLOCKSIZE][int(pos_.x + size_.x) / BLOCKSIZE] = Air;
		isShot_ = 0;
		InitializeFlag_ = 0;
	}
	// 敵に当たった  
	if (Map::mapCollision({ pos_.x - size_.x,pos_.y + size_.y }) == Enemy)
	{
		Map::mapBlock_[int(pos_.y + size_.y) / BLOCKSIZE][int(pos_.x - size_.x) / BLOCKSIZE] = Air;
		isShot_ = 0;
		InitializeFlag_ = 0;
	}
	// 敵に当たった  
	if (Map::mapCollision({ pos_.x - size_.x,pos_.y - size_.y }) == Enemy)
	{
		Map::mapBlock_[int(pos_.y - size_.y) / BLOCKSIZE][int(pos_.x - size_.x) / BLOCKSIZE] = Air;
		isShot_ = 0;
		InitializeFlag_ = 0;
	}

	// Pointに当たった  
	if (Map::mapCollision({ pos_.x + size_.x,pos_.y + size_.y }) == Point)
	{
		Map::mapBlock_[int(pos_.y + size_.y) / BLOCKSIZE][int(pos_.x + size_.x) / BLOCKSIZE] = Air;
		GameManager::Score_++;
		isShot_ = 0;
		InitializeFlag_ = 0;
	}
	// Pointに当たった  
	if (Map::mapCollision({ pos_.x + size_.x,pos_.y - size_.y }) == Point)
	{
		Map::mapBlock_[int(pos_.y - size_.y) / BLOCKSIZE][int(pos_.x + size_.x) / BLOCKSIZE] = Air;
		GameManager::Score_++;
		isShot_ = 0;
		InitializeFlag_ = 0;
	}
	// Pointに当たった  
	if (Map::mapCollision({ pos_.x - size_.x,pos_.y + size_.y }) == Point)
	{
		Map::mapBlock_[int(pos_.y + size_.y) / BLOCKSIZE][int(pos_.x - size_.x) / BLOCKSIZE] = Air;
		GameManager::Score_++;
		isShot_ = 0;
		InitializeFlag_ = 0;
	}
	// Pointに当たった  
	if (Map::mapCollision({ pos_.x - size_.x,pos_.y - size_.y }) == Point)
	{
		Map::mapBlock_[int(pos_.y - size_.y) / BLOCKSIZE][int(pos_.x - size_.x) / BLOCKSIZE] = Air;
		GameManager::Score_++;
		isShot_ = 0;
		InitializeFlag_ = 0;
	}

	// 壁に当たった 
	if (
		Map::mapCollision({ pos_.x + size_.x,pos_.y + size_.y }) == Normal ||
		Map::mapCollision({ pos_.x + size_.x,pos_.y - size_.y }) == Normal ||
		Map::mapCollision({ pos_.x - size_.x,pos_.y + size_.y }) == Normal ||
		Map::mapCollision({ pos_.x - size_.x,pos_.y - size_.y }) == Normal)
	{
		isShot_ = 0;
		InitializeFlag_ = 0;
	}

	if (pos_.y < 0 || pos_.y > 720)
	{
		isShot_ = 0;
		InitializeFlag_ = 0;
	}

}
