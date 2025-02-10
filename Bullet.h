#pragma once
#include "BaseClass.h"

class Bullet : public GameObject
{
public:
	Bullet();
	void Update(int direction);
	void Draw() override;
	void CollisionCheck();

	int GetIsShot() const { return isShot_; };
	void SetIsShot(int NEW) { isShot_ = NEW; };

private:
	int isShot_;
	int InitializeFlag_;
	int Direction_;
};