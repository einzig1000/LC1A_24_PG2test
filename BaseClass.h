#pragma once

#include <Novice.h>
#include <math.h>
#include "Functions.h"
#include "GetHitKey.h"
#include "Camera.h"

class GameObject
{
public:
	virtual void Update();
	virtual void Draw();
	virtual void Camera();

	virtual int CollisionDetection(GameObject* GameObject);

	virtual void SetPos(Vector2 pos) { pos_ = pos; }
	virtual void SetLB(Vector2 LB) { vertex_.LB = LB; }
	virtual void SetLT(Vector2 LT) { vertex_.LT = LT; }
	virtual void SetRB(Vector2 RB) { vertex_.RB = RB; }
	virtual void SetRT(Vector2 RT) { vertex_.RT = RT; }
	virtual Vector2 GetPos() const { return pos_; }
	virtual Vertex GetVertex() const { return vertex_; }

	virtual void SetDrawPos(Vector2 DrawPos) { drawpos_ = DrawPos; }
	virtual void SetDrawLB(Vector2 DrawLB) { drawvertex_.LB = DrawLB; }
	virtual void SetDrawLT(Vector2 DrawLT) { drawvertex_.LT = DrawLT; }
	virtual void SetDrawRB(Vector2 DrawRB) { drawvertex_.RB = DrawRB; }
	virtual void SetDrawRT(Vector2 DrawRT) { drawvertex_.RT = DrawRT; }
	virtual Vector2 GetDrawpos() const { return drawpos_; }
	virtual Vertex GetDrawVertex() const { return vertex_; }

	virtual void SetSize(Vector2 size) { size_ = size; }
	virtual Vector2 GetSize() const { return size_; }

	virtual void SetVelocity(Vector2 velocity) { vel_ = velocity; }
	virtual Vector2 GetVelocity() const { return vel_; }

	virtual void SetAcceleration(Vector2 acceleration) { acc_ = acceleration; }
	virtual Vector2 GetAcceleration() const { return acc_; }

	virtual void SetRadius(Vector2 radius) { rad_ = radius; }
	virtual Vector2 GetRadius() const { return rad_; };

	virtual int GetObjectID() const { return ObjectID; };

	virtual unsigned int GetColor() const { return (R_ << 24) + (G_ << 16) + (B_ << 8) + (A_); };


	Vector2 add(Vector2 A, Vector2 B) { return { A.x + B.x, A.y + B.y }; };



protected:
	int white1x1 = Novice::LoadTexture("./NoviceResources/white1x1.png");
	Vector2 pos_;
	Vertex vertex_;
	Vector2 drawpos_;
	Vertex drawvertex_;

	Vector2 size_ = { 0,0 };
	Vector2	vel_ = { 0,0 };
	Vector2 absVel_ = { 0,0 };
	Vector2 acc_ = { 0,0 };
	Vector2 rad_ = { 0,0 };

	Vector2 Scale_ = { 1,1 };
	float Rotate_ = 0;
	Vector2 Translate_ = { 0,0 };
	Matrix3x3 SRT_;


	float mass_ = 0;
	int R_ = 0xFF;
	int G_ = 0xFF;
	int B_ = 0xFF;
	int A_ = 0xFF;
	int ObjectID = 0;
};