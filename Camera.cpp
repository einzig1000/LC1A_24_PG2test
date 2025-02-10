#include "Camera.h"
#include "Player.h"

Matrix3x3 Camera::wvpVpMatrix;

Camera::Camera()
{
	// ワールド上のカメラ座標
	cameraWorldPos = { 0,0 };
	// カメラの原点
	cameratranslate = { float(WINDOW_WIDTH / 2) - 10, float(WINDOW_HEIGHT / 2) - 10 };
	cameraWorldPos.x = cameratranslate.x;
	cameraWorldPos.y = cameratranslate.y;
	// 拡大率
	cameraScale = { 1.0f ,1.0f };
	// 回転
	cameraRotate = 0;
	// ワールドの原点
	worldPos = { 0.0f ,0.0f };
	// 左上
	cameraLeftTop = { float(-WINDOW_WIDTH / 2) ,float(WINDOW_HEIGHT / 2) };
	// 右下
	cameraRightBottom = { float(WINDOW_WIDTH / 2) ,float(-WINDOW_HEIGHT / 2) };
	// 幅と高さ
	cameraWidth = float(WINDOW_WIDTH);
	cameraHeight = float(WINDOW_HEIGHT);

	// ワールドの行列
	worldMatrix = MakeAffineMatrix(cameraScale, 0.0f, worldPos);
	// ビュー行列
	cameraMatrix = MakeTranslateMatrix(cameraWorldPos);
	// ビュー行列の逆行列
	viewMatrix = Inverse(cameraMatrix);
	// 正射影行列
	orthoMatrix = MakeOrthographicMatrix(cameraLeftTop.x, cameraLeftTop.y, cameraRightBottom.x, cameraRightBottom.y);
	// ビューポート行列
	viewportMatrix = MakeViewPortMatrix(0, 0, cameraWidth, cameraHeight);
	// 合成したカメラの行列
	wvpVpMatrix;
}

Camera::~Camera() {}

// 正射影行列作成関数
Matrix3x3 Camera::MakeOrthographicMatrix(float left, float top, float right, float bottom)
{
	Matrix3x3 resultMatrix{};

	resultMatrix.m[0][0] = 2.0f / (right - left);
	resultMatrix.m[0][1] = 0.0f;
	resultMatrix.m[0][2] = 0.0f;
	resultMatrix.m[1][0] = 0.0f;
	resultMatrix.m[1][1] = 2.0f / (top - bottom);
	resultMatrix.m[1][2] = 0.0f;
	resultMatrix.m[2][0] = (left + right) / (left - right);
	resultMatrix.m[2][1] = (top + bottom) / (bottom - top);
	resultMatrix.m[2][2] = 1.0f;

	return resultMatrix;
}

// ビューポート行列作成関数
Matrix3x3 Camera::MakeViewPortMatrix(float left, float top, float width, float height)
{
	Matrix3x3 resultMatrix{};

	resultMatrix.m[0][0] = width / 2.0f;
	resultMatrix.m[0][1] = 0.0f;
	resultMatrix.m[0][2] = 0.0f;
	resultMatrix.m[1][0] = 0.0f;
	resultMatrix.m[1][1] = -height / 2.0f;
	resultMatrix.m[1][2] = 0.0f;
	resultMatrix.m[2][0] = left + width / 2.0f;
	resultMatrix.m[2][1] = top + height / 2.0f;
	resultMatrix.m[2][2] = 1.0f;

	return resultMatrix;
}

// 行列の積作成関数
Matrix3x3 Camera::Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2)
{
	Matrix3x3 resultMatrix{};

	resultMatrix.m[0][0] = matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0] + matrix1.m[0][2] * matrix2.m[2][0];
	resultMatrix.m[0][1] = matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1] + matrix1.m[0][2] * matrix2.m[2][1];
	resultMatrix.m[0][2] = matrix1.m[0][0] * matrix2.m[0][2] + matrix1.m[0][1] * matrix2.m[1][2] + matrix1.m[0][2] * matrix2.m[2][2];

	resultMatrix.m[1][0] = matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0] + matrix1.m[1][2] * matrix2.m[2][0];
	resultMatrix.m[1][1] = matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1] + matrix1.m[1][2] * matrix2.m[2][1];
	resultMatrix.m[1][2] = matrix1.m[1][0] * matrix2.m[0][2] + matrix1.m[1][1] * matrix2.m[1][2] + matrix1.m[1][2] * matrix2.m[2][2];

	resultMatrix.m[2][0] = matrix1.m[2][0] * matrix2.m[0][0] + matrix1.m[2][1] * matrix2.m[1][0] + matrix1.m[2][2] * matrix2.m[2][0];
	resultMatrix.m[2][1] = matrix1.m[2][0] * matrix2.m[0][1] + matrix1.m[2][1] * matrix2.m[1][1] + matrix1.m[2][2] * matrix2.m[2][1];
	resultMatrix.m[2][2] = matrix1.m[2][0] * matrix2.m[0][2] + matrix1.m[2][1] * matrix2.m[1][2] + matrix1.m[2][2] * matrix2.m[2][2];

	return resultMatrix;
}

// 逆行列作成関数
Matrix3x3 Camera::Inverse(Matrix3x3 matrix)
{

	Matrix3x3 resultMatrix{};

	resultMatrix.m[0][0] = matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1];
	resultMatrix.m[0][1] = -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]);
	resultMatrix.m[0][2] = matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1];

	resultMatrix.m[1][0] = -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]);
	resultMatrix.m[1][1] = matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0];
	resultMatrix.m[1][2] = -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]);

	resultMatrix.m[2][0] = matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0];
	resultMatrix.m[2][1] = -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]);
	resultMatrix.m[2][2] = matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0];

	return resultMatrix;

}

// 平行移動行列の関数
Matrix3x3 Camera::MakeTranslateMatrix(Vector2 translate)
{
	Matrix3x3 translateMatrix{};

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			translateMatrix.m[i][j] = { 0 };
		}
	}

	translateMatrix.m[0][0] = { 1 };
	translateMatrix.m[2][0] = { translate.x };

	translateMatrix.m[1][1] = { 1 };
	translateMatrix.m[2][1] = { translate.y };

	translateMatrix.m[2][2] = { 1 };

	return translateMatrix;
}

// アフィン
Matrix3x3 Camera::MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate)
{
	Matrix3x3 scaleMatrix{};
	Matrix3x3 rotateMatrix{};
	Matrix3x3 translateMatrix{};
	Matrix3x3 resultMatrix{};

	// 拡縮行列
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			scaleMatrix.m[i][j] = 0.0f;
		}
	}
	scaleMatrix.m[0][0] = scale.x;
	scaleMatrix.m[1][1] = scale.y;
	scaleMatrix.m[2][2] = 1.0f;

	// 回転行列
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			rotateMatrix.m[i][j] = 0.0f;
		}
	}
	rotateMatrix.m[0][0] = cosf(rotate);
	rotateMatrix.m[0][1] = sinf(rotate);
	rotateMatrix.m[1][0] = -sinf(rotate);
	rotateMatrix.m[1][1] = cosf(rotate);
	rotateMatrix.m[2][2] = 1.0f;

	// 移動行列
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			translateMatrix.m[i][j] = 0.0f;
		}
	}
	translateMatrix.m[0][0] = 1.0f;
	translateMatrix.m[1][1] = 1.0f;
	translateMatrix.m[2][0] = translate.x;
	translateMatrix.m[2][1] = translate.y;
	translateMatrix.m[2][2] = 1.0f;

	// 行列の結合
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			resultMatrix.m[i][j] = 0.0f;
		}
	}

	resultMatrix.m[0][0] = scaleMatrix.m[0][0] * rotateMatrix.m[0][0] + scaleMatrix.m[0][1] * rotateMatrix.m[1][0] + scaleMatrix.m[0][2] * rotateMatrix.m[2][0];
	resultMatrix.m[0][1] = scaleMatrix.m[0][0] * rotateMatrix.m[0][1] + scaleMatrix.m[0][1] * rotateMatrix.m[1][1] + scaleMatrix.m[0][2] * rotateMatrix.m[2][1];
	resultMatrix.m[0][2] = scaleMatrix.m[0][0] * rotateMatrix.m[0][2] + scaleMatrix.m[0][1] * rotateMatrix.m[1][2] + scaleMatrix.m[0][2] * rotateMatrix.m[2][2];

	resultMatrix.m[1][0] = scaleMatrix.m[1][0] * rotateMatrix.m[0][0] + scaleMatrix.m[1][1] * rotateMatrix.m[1][0] + scaleMatrix.m[1][2] * rotateMatrix.m[2][0];
	resultMatrix.m[1][1] = scaleMatrix.m[1][0] * rotateMatrix.m[0][1] + scaleMatrix.m[1][1] * rotateMatrix.m[1][1] + scaleMatrix.m[1][2] * rotateMatrix.m[2][1];
	resultMatrix.m[1][2] = scaleMatrix.m[1][0] * rotateMatrix.m[0][2] + scaleMatrix.m[1][1] * rotateMatrix.m[1][2] + scaleMatrix.m[1][2] * rotateMatrix.m[2][2];

	resultMatrix.m[2][0] = scaleMatrix.m[2][0] * rotateMatrix.m[0][0] + scaleMatrix.m[2][1] * rotateMatrix.m[1][0] + scaleMatrix.m[2][2] * rotateMatrix.m[2][0];
	resultMatrix.m[2][1] = scaleMatrix.m[2][0] * rotateMatrix.m[0][1] + scaleMatrix.m[2][1] * rotateMatrix.m[1][1] + scaleMatrix.m[2][2] * rotateMatrix.m[2][1];
	resultMatrix.m[2][2] = scaleMatrix.m[2][0] * rotateMatrix.m[0][2] + scaleMatrix.m[2][1] * rotateMatrix.m[1][2] + scaleMatrix.m[2][2] * rotateMatrix.m[2][2];

	resultMatrix.m[0][0] = resultMatrix.m[0][0] * translateMatrix.m[0][0] + resultMatrix.m[0][1] * translateMatrix.m[1][0] + resultMatrix.m[0][2] * translateMatrix.m[2][0];
	resultMatrix.m[0][1] = resultMatrix.m[0][0] * translateMatrix.m[0][1] + resultMatrix.m[0][1] * translateMatrix.m[1][1] + resultMatrix.m[0][2] * translateMatrix.m[2][1];
	resultMatrix.m[0][2] = resultMatrix.m[0][0] * translateMatrix.m[0][2] + resultMatrix.m[0][1] * translateMatrix.m[1][2] + resultMatrix.m[0][2] * translateMatrix.m[2][2];

	resultMatrix.m[1][0] = resultMatrix.m[1][0] * translateMatrix.m[0][0] + resultMatrix.m[1][1] * translateMatrix.m[1][0] + resultMatrix.m[1][2] * translateMatrix.m[2][0];
	resultMatrix.m[1][1] = resultMatrix.m[1][0] * translateMatrix.m[0][1] + resultMatrix.m[1][1] * translateMatrix.m[1][1] + resultMatrix.m[1][2] * translateMatrix.m[2][1];
	resultMatrix.m[1][2] = resultMatrix.m[1][0] * translateMatrix.m[0][2] + resultMatrix.m[1][1] * translateMatrix.m[1][2] + resultMatrix.m[1][2] * translateMatrix.m[2][2];

	resultMatrix.m[2][0] = resultMatrix.m[2][0] * translateMatrix.m[0][0] + resultMatrix.m[2][1] * translateMatrix.m[1][0] + resultMatrix.m[2][2] * translateMatrix.m[2][0];
	resultMatrix.m[2][1] = resultMatrix.m[2][0] * translateMatrix.m[0][1] + resultMatrix.m[2][1] * translateMatrix.m[1][1] + resultMatrix.m[2][2] * translateMatrix.m[2][1];
	resultMatrix.m[2][2] = resultMatrix.m[2][0] * translateMatrix.m[0][2] + resultMatrix.m[2][1] * translateMatrix.m[1][2] + resultMatrix.m[2][2] * translateMatrix.m[2][2];

	return resultMatrix;
}

// 2次元ベクトルを同次座標として変換する関数
Vector2 Camera::Transform(Vector2 vector, Matrix3x3 matrix)
{
	Vector2 result{};

	// ベクトルと行列の計算
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];

	// wが0でなければ
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;

	// 計算結果をVector2型で返す
	return result;
}

void Camera::ChangeTransrate(Player* player)
{
	// 矢印キーで上下左右に移動
	if (GetHitKey::keys[DIK_UP])cameratranslate.y += 5.0f;
	if (GetHitKey::keys[DIK_DOWN])cameratranslate.y -= 5.0f;
	if (GetHitKey::keys[DIK_RIGHT])cameratranslate.x += 5.0f;
	if (GetHitKey::keys[DIK_LEFT])cameratranslate.x -= 5.0f;



	cameraWorldPos.x = cameratranslate.x + player->GetPos().x;
	cameraWorldPos.y = cameratranslate.y + player->GetPos().y;
	cameraWorldPos.x = cameratranslate.x;
	cameraWorldPos.y = cameratranslate.y;
}

void Camera::ChangeScale()
{
	if (GetHitKey::keys[DIK_X])
	{
		cameraScale.x += 0.01f;
		cameraScale.y += 0.01f;
	}
	if (GetHitKey::keys[DIK_Z])
	{
		cameraScale.x -= 0.01f;
		cameraScale.y -= 0.01f;
	}
}

void Camera::ChangeRatate()
{
	if (GetHitKey::keys[DIK_C])
	{
		cameraRotate += 0.1f;
	}
}

void Camera::Update(Player* player)
{
	ChangeTransrate(player);
	ChangeScale();
	ChangeRatate();
	// ビュー行列
	//cameraMatrix = MakeTranslateMatrix(cameraWorldPos);
	// カメラ行列
	cameraMatrix = MakeAffineMatrix(cameraScale, cameraRotate, cameraWorldPos);
	// ビュー行列
	viewMatrix = Inverse(cameraMatrix);
	// 正射影行列
	orthoMatrix = MakeOrthographicMatrix(static_cast<float>(-WINDOW_WIDTH / 2.0f), static_cast<float>(WINDOW_HEIGHT / 2.0f), static_cast<float>(WINDOW_WIDTH / 2.0f), static_cast<float>(-WINDOW_HEIGHT / 2.0f));
	// ビューポート行列
	viewportMatrix = MakeViewPortMatrix(0, 0, static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT));
	// 行列の結合
	//wvpVpMatrix = Multiply(worldMatrix, viewMatrix);
	wvpVpMatrix = Multiply(viewMatrix, orthoMatrix);
	wvpVpMatrix = Multiply(wvpVpMatrix, viewportMatrix);
}