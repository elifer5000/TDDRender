#pragma once

//TODO: This should be centralized in one header with each export
#ifdef BASICMATH_EXPORTS
#define CLASS_DECLSPEC    __declspec(dllexport)
#else
#define CLASS_DECLSPEC    __declspec(dllimport)
#endif

#define EPSILON 0.00001f

CLASS_DECLSPEC bool isEqualf(float a, float b);

/**
* Returns:
* a > b -> 1
* b > a -> -1
* a == b -> 0
*/
CLASS_DECLSPEC short comp(float a, float b);