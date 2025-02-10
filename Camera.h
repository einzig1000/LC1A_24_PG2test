#pragma once
#include <Novice.h>
#include <cmath>
#include <cassert>
#include "GetHitKey.h"
#include "definition.h"
//#include "Player.h"

class Player;


class Camera
{
public:
	Camera();
	~Camera();

public:

	// 正射影行列作成関数
	Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom);
	// ビューポート行列作成関数
	Matrix3x3 MakeViewPortMatrix(float left, float top, float width, float height);
	// 行列の積作成関数
	Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);
	// 逆行列作成関数
	Matrix3x3 Inverse(Matrix3x3 matrix);
	// 平行移動行列の関数
	Matrix3x3 MakeTranslateMatrix(Vector2 translate);
	// アフィン行列作成関数
	Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate);
	// 2次元ベクトルを同次座標として変換する関数
	Vector2 Transform(Vector2 vector, Matrix3x3 matrix);
	void ChangeTransrate(Player* player);
	void ChangeScale();
	void ChangeRatate();
	void Update(Player* player);


public:
	// カメラ
	Vector2 cameraWorldPos;
	Vector2 cameratranslate;
	Vector2 cameraScale;
	float cameraRotate;

	Vector2 worldPos;
	Vector2 cameraLeftTop;
	Vector2 cameraRightBottom;
	float cameraWidth;
	float cameraHeight;
	// ワールドの行列
	Matrix3x3 worldMatrix;
	// ビュー行列
	Matrix3x3 cameraMatrix;
	// ビュー行列の逆行列
	Matrix3x3 viewMatrix;
	// 正射影行列
	Matrix3x3 orthoMatrix;
	// ビューポート行列
	Matrix3x3 viewportMatrix;
	// 合成したカメラの行列
	static Matrix3x3 wvpVpMatrix;
};