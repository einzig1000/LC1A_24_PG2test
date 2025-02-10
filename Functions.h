#pragma once
#include "definition.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <assert.h>



Matrix3x3 MakeMatrix(Vector2 translate, Vector2 scale, float theta);
Vector2 Transform(Vector2 vector, Matrix3x3 matrix);