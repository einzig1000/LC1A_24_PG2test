#pragma once
#include <Novice.h>
#include <math.h>
#include "definition.h"
#define pointSum 26


class Count
{
public:
	Count();
	void Update(int startnum, int endnum, Vector2 pos, Vector2 size);
	void Draw();

	void targetChange(int targetnum);


private:
	Vector2 pos_[pointSum];
	Vector2 UnitVector_[pointSum];
	Vector2 targetpos_[pointSum];
	Vector2 targetposbuf_;
	Vector2 drawpos_;
	Vector2 radius_;
	float length_;
	int nextnum_;
	int frame_;
	int preframe_;
	bool countFlag_;
};

