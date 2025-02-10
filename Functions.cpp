#include "Functions.h"


Matrix3x3 MakeMatrix(Vector2 translate, Vector2 scale, float theta)
{

	Matrix3x3 srt{};
	srt.m[0][0] = scale.x * cosf(theta);		//0行0列
	srt.m[0][1] = scale.x * sinf(theta);		//0行1列
	srt.m[0][2] = 0;							//0行2列
	srt.m[1][0] = -scale.y * sinf(theta);		//1行0列
	srt.m[1][1] = scale.y * cosf(theta);		//1行1列
	srt.m[1][2] = 0;							//1行2列
	srt.m[2][0] = translate.x;					//2行0列
	srt.m[2][1] = translate.y;					//2行1列
	srt.m[2][2] = 1;							//2行2列
	return srt;

	// [ 拡縮Ｘ * cosf(theta)    拡縮Ｘ * sinf(theta)   0]
	// [-拡縮Ｙ * sinf(theta)    拡縮Ｙ * cosf(theta)   0]
	// [平行移動Ｘ               平行移動Ｙ             1]
}

Vector2 Transform(Vector2 vector, Matrix3x3 matrix)
{
	Vector2 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	return result;
}