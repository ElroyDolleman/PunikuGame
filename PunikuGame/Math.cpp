#include "Math.h"

float Math::Max(float value1, float value2)
{
	if (value1 > value2)
		return value1;
	return value2;
}

float Math::Min(float value1, float value2)
{
	if (value1 < value2)
		return value1;
	return value2;
}

float Math::Clamp(float value, float min, float max)
{
	return Min(Max(value, min), max);
}