#include "ChangeScene.h"

ChangeScene::ChangeScene()
{
	VetexSum = 5;
	size = 1280;
	rad = 0;
	initialize = 0;
	for (int i = 0; i < 60; i++)
	{
		vertex[i] = { -5000,-5000 };
	}
}

void ChangeScene::stages2(int count, int countMax1, int countMax2, int cooltime, int vertexSum, Vector2 center, float size0, float size1, float size2)
{
	if (initialize == 0)
	{
		size = size0;
		initialize = 1;
	}
	VetexSum = vertexSum;
	rad = 360.0f / VetexSum;
	pos = { center.x ,center.y };
	vertex[0] = { 0, size };

	if (count < countMax1)
	{
		size = Easings::LINER(count, countMax1, size0, size1);
	}
	if ((count >= (cooltime + countMax1)) && ((count - (cooltime + countMax1)) <= countMax2))
	{
		size = Easings::LINER(count - (cooltime + countMax1), countMax2, size1, -size2);
	}

	for (int i = 1; i < VetexSum; i++)
	{
		vertex[i] = { vertex[i - 1].x * cosf(rad / 180.0f * m_pi) - vertex[i - 1].y * sinf(rad / 180.0f * m_pi), vertex[i - 1].x * sinf(rad / 180.0f * m_pi) + vertex[i - 1].y * cosf(rad / 180.0f * m_pi) };
	}
}

void ChangeScene::Draw()
{
	for (int i = 0; i < VetexSum; i++)
	{
		Novice::DrawBox(int(vertex[i].x + pos.x), int(vertex[i].y + pos.y), 3000, 3000, (((rad / 2) + (rad * i)) / 180.0f * m_pi), BLACK, kFillModeSolid);
		Novice::DrawBox(int(vertex[i].x + pos.x), int(vertex[i].y + pos.y), 3000, 3000, ((((rad / 2) + ((rad / 2) / 2)) + (rad * i)) / 180.0f * m_pi), BLACK, kFillModeSolid);
	}
}