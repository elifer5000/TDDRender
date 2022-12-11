#pragma once

#include "Export.h"

#define EPSILON 0.00001f

template<typename T> bool isEqualTemplate(T a, T b) {
	//OutputDebugString(L"Hello");
	//_ASSERT(true);
	return abs(a - b) < EPSILON;
}

#define isEqualf isEqualTemplate<float>
#define isEquald isEqualTemplate<double>

/**
* Returns:
* a > b -> 1
* b > a -> -1
* a == b -> 0
*/
BASICMATH_DECLSPEC short comp(double a, double b);

BASICMATH_DECLSPEC double rad2deg(double rad);
