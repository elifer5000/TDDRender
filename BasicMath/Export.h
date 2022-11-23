#pragma once

#ifdef BASICMATH_EXPORTS
#define BASICMATH_DECLSPEC    __declspec(dllexport)
#define BASICMATH_EXTERN
#else
#define BASICMATH_DECLSPEC    __declspec(dllimport)
#define BASICMATH_EXTERN extern
#endif