#pragma once
#include "Object.h"

class RAYTRACER_DECLSPEC Sphere : public Object {
public:
	Sphere() {}

	Intersections intersect(const Ray& ray) const override;
};