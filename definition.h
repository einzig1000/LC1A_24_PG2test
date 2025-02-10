#pragma once

/*/////////////////////////////////////////
				 define
/////////////////////////////////////////*/
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

//#define MAP_WIDTH 13
//#define MAP_HEIGHT 20
//#define BLOCKSIZE 60
#define MAP_HEIGHT 120
#define MAP_WIDTH 36
#define BLOCKSIZE 20

#define BulletSum 10

/*/////////////////////////////////////////
				  struct
/////////////////////////////////////////*/
struct Vector2
{
 	float x = 0;
	float y = 0;
};

struct Matrix3x3
{
	float m[3][3] = {
	{ 0,0,0 },
	{ 0,0,0 },
	{ 0,0,0 } };
};

struct Vertex
{
	Vector2 LT = { 0,0 };
	Vector2 RT = { 0,0 };
	Vector2 LB = { 0,0 };
	Vector2 RB = { 0,0 };
};

struct  Block
{
	Vector2 pos;
	Vertex vertexPos;
	Vertex drawvertex_;
};

/*/////////////////////////////////////////
				   enum
/////////////////////////////////////////*/
enum Scene
{
	TITLE = 0,
	GAME_PLAY = 1,
	RESULT = 2,
};

enum BlockID
{
	Air = 0,
	Normal = 1,
	Enemy = 2,
	Point = 3,
};

enum ObjectId
{
	ID_Player = 1,
	ID_Enemy = 2,
};

enum DirectionID
{
	Left = 0,
	Right = 1,
	Top = 2,
	Bottom = 3,
	LT = 4,
	LB = 5,
	RT = 6,
	RB = 7,
};