#include "pch.h"
#include <cmath>
#include "Utils.h"

bool isEqual(float a, float b) {
	//OutputDebugString(L"Hello");
	//_ASSERT(true);
	return abs(a - b) < EPSILON;
}

short comp(float a, float b) {
	float r = a - b;

	if (r > EPSILON) {
		return 1;
	}
	else if (r < -EPSILON) {
		return -1;
	}

	return 0;
}