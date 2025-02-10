#include "GetHitKey.h"

char GetHitKey::keys[256];
char GetHitKey::preKeys[256];

void GetHitKey::Update()
{
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);
}