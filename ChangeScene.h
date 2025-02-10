#pragma once
#include <Novice.h>
#include "Easings.h"
#include "definition.h"

class ChangeScene
{
public:

	ChangeScene();

	/// <summary>
	/// 2段階で見える範囲を調整する。(一部を映したあと全部消す)
	/// </summary>
	/// <param name="count">現在のカウント</param>
	/// <param name="countMax1">１段階目のカウントの最大値</param>
	/// <param name="countMax2">２段階目のカウントの最大値</param>
	/// <param name="cooltime">１段階目と２段階目の間</param>
	/// <param name="vertexSum">頂点数</param>
	/// <param name="center">中心座標(Drawに使っている数値)</param>
	/// <param name="size0">最初に映っている部分のサイズ</param>
	/// <param name="size1">１段階目に映っている部分のサイズ</param>
	/// <param name="size2">２段階目に映っている部分のサイズ</param>
	void stages2(int count, int countMax1, int countMax2, int cooltime, int vertexSum, Vector2 center, float size0, float size1, float size2);
	void Draw();

	float m_pi = 3.14159265f;
	int VetexSum;
	float rad;
	float size;
	Vector2 pos;
	Vector2 vertex[60] = {};

	float mainRad = 0;
	int initialize = 0;
};