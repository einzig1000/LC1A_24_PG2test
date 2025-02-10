#include "BaseClass.h"
#include "Functions.h"
#include "assert.h"

void GameObject::Update() {}
void GameObject::Draw() {}

void GameObject::Camera()
{
	Matrix3x3 matrix = Camera::wvpVpMatrix;
	// 中心
	{
		drawpos_.x = pos_.x * matrix.m[0][0] + pos_.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
		drawpos_.y = pos_.x * matrix.m[0][1] + pos_.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];

		float w = pos_.x * matrix.m[0][2] + pos_.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];

		assert(w != 0.0f);
		drawpos_.x /= w;
		drawpos_.y /= w;
	};
	// LT
	{
		drawvertex_.LT.x = vertex_.LT.x * matrix.m[0][0] + vertex_.LT.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
		drawvertex_.LT.y = vertex_.LT.x * matrix.m[0][1] + vertex_.LT.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];

		float w = vertex_.LT.x * matrix.m[0][2] + vertex_.LT.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];

		assert(w != 0.0f);
		drawvertex_.LT.x /= w;
		drawvertex_.LT.y /= w;
	};
	// RT
	{
		drawvertex_.RT.x = vertex_.RT.x * matrix.m[0][0] + vertex_.RT.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
		drawvertex_.RT.y = vertex_.RT.x * matrix.m[0][1] + vertex_.RT.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];

		float w = vertex_.RT.x * matrix.m[0][2] + vertex_.RT.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];

		assert(w != 0.0f);
		drawvertex_.RT.x /= w;
		drawvertex_.RT.y /= w;
	};
	// LT
	{
		drawvertex_.LB.x = vertex_.LB.x * matrix.m[0][0] + vertex_.LB.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
		drawvertex_.LB.y = vertex_.LB.x * matrix.m[0][1] + vertex_.LB.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];

		float w = vertex_.LB.x * matrix.m[0][2] + vertex_.LB.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];

		assert(w != 0.0f);
		drawvertex_.LB.x /= w;
		drawvertex_.LB.y /= w;
	};
	// RB
	{
		drawvertex_.RB.x = vertex_.RB.x * matrix.m[0][0] + vertex_.RB.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
		drawvertex_.RB.y = vertex_.RB.x * matrix.m[0][1] + vertex_.RB.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];

		float w = vertex_.RB.x * matrix.m[0][2] + vertex_.RB.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];

		assert(w != 0.0f);
		drawvertex_.RB.x /= w;
		drawvertex_.RB.y /= w;
	};


	SRT_ = MakeMatrix(Translate_, Scale_, Rotate_);

	Vertex AAA = drawvertex_;

	drawvertex_.LT = add(Transform({ AAA.LT.x - drawpos_.x, AAA.LT.y - drawpos_.y }, SRT_), drawpos_);
	drawvertex_.RT = add(Transform({ AAA.RT.x - drawpos_.x, AAA.RT.y - drawpos_.y }, SRT_), drawpos_);
	drawvertex_.LB = add(Transform({ AAA.LB.x - drawpos_.x, AAA.LB.y - drawpos_.y }, SRT_), drawpos_);
	drawvertex_.RB = add(Transform({ AAA.RB.x - drawpos_.x, AAA.RB.y - drawpos_.y }, SRT_), drawpos_);
}

int GameObject::CollisionDetection(GameObject* GameObject)
{
	Vector2 radius = GameObject->GetRadius();
	// ここで当たり判定する

	Vector2 VectorPosGap = {};
	if (pos_.x >= GameObject->GetPos().x)VectorPosGap.x = pos_.x - GameObject->GetPos().x;
	else VectorPosGap.x = GameObject->GetPos().x - pos_.x;

	if (pos_.y >= GameObject->GetPos().y)VectorPosGap.y = pos_.y - GameObject->GetPos().y;
	else VectorPosGap.y = GameObject->GetPos().y - pos_.y;

	// 直線距離
	float PosGap = 0;
	PosGap = sqrtf((VectorPosGap.x * VectorPosGap.x) + (VectorPosGap.y * VectorPosGap.y));


	if (PosGap < (rad_.x + radius.x))
	{
		return 1;
	}
	else return 0;
}