#pragma once

#ifdef RAYTRACER_EXPORTS
#define RAYTRACER_DECLSPEC    __declspec(dllexport)
#define RAYTRACER_EXTERN
#else
#define RAYTRACER_DECLSPEC    __declspec(dllimport)
#define RAYTRACER_EXTERN extern
#endif