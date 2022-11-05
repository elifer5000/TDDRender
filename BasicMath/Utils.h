#pragma once

#include "Export.h"

#define EPSILON 0.00001f

CLASS_DECLSPEC bool isEqualf(float a, float b);

/**
* Returns:
* a > b -> 1
* b > a -> -1
* a == b -> 0
*/
CLASS_DECLSPEC short comp(float a, float b);