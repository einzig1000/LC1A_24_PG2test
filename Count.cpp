#include "Count.h"

Count::Count()
{
	for (int i = 0; i < pointSum; ++i)
	{
		pos_[i] = { 0,0 };
		UnitVector_[i] = { 0,0 };
		targetpos_[i] = { 0,0 };
	}
	drawpos_ = { 0,0 };
	radius_ = { 1,1 };
	targetposbuf_ = { 0,0 };
	nextnum_ = -23;
	frame_ = 0;
	length_ = 0;
	preframe_ = 0;
	countFlag_ = 1;
}

void Count::Update(int startnum, int endnum, Vector2 pos, Vector2 size)
{
	if (countFlag_ == 1)
	{
		drawpos_ = pos;
		radius_.x = size.x;
		radius_.y = size.y;
		if (frame_ % 60 == 0 && endnum != nextnum_)
		{
			preframe_ = frame_;
			nextnum_ = startnum;
			if (startnum <= endnum)nextnum_ += (frame_ / 60);
			else nextnum_ -= (frame_ / 60);
			targetChange(nextnum_);

			for (int i = 0; i < pointSum; ++i)
			{
				targetpos_[i].x *= size.x;
				targetpos_[i].y *= size.y;

				UnitVector_[i].x = (targetpos_[i].x - pos_[i].x) / 20;
				UnitVector_[i].y = (targetpos_[i].y - pos_[i].y) / 20;
			}
		}
		else if (frame_ % 60 == 0 && endnum == nextnum_)
		{
			countFlag_ = 0;
		}
		if (frame_ - preframe_ < 20)
		{
			for (int i = 0; i < pointSum; ++i)
			{
				pos_[i].x += UnitVector_[i].x;
				pos_[i].y += UnitVector_[i].y;
			}
		}
		frame_++;
	}
}

void Count::Draw()
{
	if (countFlag_ == 1)
	{
		for (int i = 0; i < pointSum; ++i)
		{
			Novice::DrawEllipse(int(pos_[i].x + drawpos_.x), int(pos_[i].y + drawpos_.y), int(radius_.x), int(radius_.y), 0, WHITE, kFillModeSolid);
		}
	}
}

void Count::targetChange(int targetnum)
{
	if (targetnum == 0)
	{
		targetpos_[0] = { 0,-6 };
		targetpos_[1] = { 1,-5 };
		targetpos_[2] = { 2,-4 };
		targetpos_[3] = { 2,-3 };
		targetpos_[4] = { 2,-2 };
		targetpos_[5] = { 2,-1 };
		targetpos_[6] = { 2,0 };
		targetpos_[7] = { 2,1 };
		targetpos_[8] = { 2,2 };
		targetpos_[9] = { 2,3 };
		targetpos_[10] = { 2,4 };
		targetpos_[11] = { 1,5 };
		targetpos_[12] = { 0,6 };
		targetpos_[13] = { -1,6 };
		targetpos_[14] = { -2,5 };
		targetpos_[15] = { -3,4 };
		targetpos_[16] = { -3,3 };
		targetpos_[17] = { -3,2 };
		targetpos_[18] = { -3,1 };
		targetpos_[19] = { -3,0 };
		targetpos_[20] = { -3,-1 };
		targetpos_[21] = { -3,-2 };
		targetpos_[22] = { -3,-3 };
		targetpos_[23] = { -3,-4 };
		targetpos_[24] = { -2,-5 };
		targetpos_[25] = { -1,-6 };
	}
	else if (targetnum == 1)
	{
		targetpos_[0] = { -2,-5 };
		targetpos_[1] = { -1,-5 };
		targetpos_[2] = { 0,-6 };
		targetpos_[3] = { 0,-5 };
		targetpos_[4] = { 0,-4 };
		targetpos_[5] = { 0,-3 };
		targetpos_[6] = { 0,-2 };
		targetpos_[7] = { 0,-1 };
		targetpos_[8] = { 0,0 };
		targetpos_[9] = { 0,1 };
		targetpos_[10] = { 0,2 };
		targetpos_[11] = { 0,3 };
		targetpos_[12] = { 0,4 };
		targetpos_[13] = { 0,5 };
		targetpos_[14] = { 0,6 };
		targetpos_[15] = { -2,6 };
		targetpos_[16] = { -1,6 };
		targetpos_[17] = { 0,6 };
		targetpos_[18] = { 1,6 };
		targetpos_[19] = { 1,6 };
		targetpos_[20] = { 1,6 };
		targetpos_[21] = { 1,6 };
		targetpos_[22] = { 1,6 };
		targetpos_[23] = { 1,6 };
		targetpos_[24] = { 1,6 };
		targetpos_[25] = { 1,6 };
	}
	else if (targetnum == 2)
	{
		targetpos_[0] = { -3,-3 };
		targetpos_[1] = { -3,-4 };
		targetpos_[2] = { -2,-5 };
		targetpos_[3] = { -1,-6 };
		targetpos_[4] = { 0,-6 };
		targetpos_[5] = { 1,-5 };
		targetpos_[6] = { 2,-4 };
		targetpos_[7] = { 2,-3 };
		targetpos_[8] = { 2,-2 };
		targetpos_[9] = { 1,-1 };
		targetpos_[10] = { 1,0 };
		targetpos_[11] = { 0,1 };
		targetpos_[12] = { -1,2 };
		targetpos_[13] = { -1,3 };
		targetpos_[14] = { -2,4 };
		targetpos_[15] = { -3,5 };
		targetpos_[16] = { -3,6 };
		targetpos_[17] = { -2,6 };
		targetpos_[18] = { -1,6 };
		targetpos_[19] = { 0,6 };
		targetpos_[20] = { 1,6 };
		targetpos_[21] = { 2,6 };
		targetpos_[22] = { 2,6 };
		targetpos_[23] = { 2,6 };
		targetpos_[24] = { 2,6 };
		targetpos_[25] = { 2,6 };
	}
	else if (targetnum == 3)
	{
		targetpos_[0] = { -3,-3 };
		targetpos_[1] = { -3,-4 };
		targetpos_[2] = { -2,-5 };
		targetpos_[3] = { -1,-6 };
		targetpos_[4] = { 0,-6 };
		targetpos_[5] = { 1,-5 };
		targetpos_[6] = { 2,-4 };
		targetpos_[7] = { 2,-3 };
		targetpos_[8] = { 2,-2 };
		targetpos_[9] = { 1,-1 };
		targetpos_[10] = { 0,0 };
		targetpos_[11] = { -1,0 };
		targetpos_[12] = { 0,0 };
		targetpos_[13] = { 1,1 };
		targetpos_[14] = { 2,2 };
		targetpos_[15] = { 2,3 };
		targetpos_[16] = { 2,4 };
		targetpos_[17] = { 1,5 };
		targetpos_[18] = { 0,6 };
		targetpos_[19] = { -1,6 };
		targetpos_[20] = { -2,5 };
		targetpos_[21] = { -3,4 };
		targetpos_[22] = { -3,3 };
		targetpos_[23] = { -3,3 };
		targetpos_[24] = { -3,3 };
		targetpos_[25] = { -3,3 };
	}

	// target配列の順番を入れ替える
	for (int i = 0; i < 30; ++i)
	{
		int X = rand() % pointSum;
		int Y = rand() % pointSum;
		targetposbuf_ = targetpos_[X];
		targetpos_[X] = targetpos_[Y];
		targetpos_[Y] = targetposbuf_;
	}
}
