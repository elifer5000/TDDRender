#pragma once
#include "Object.h"

class RAYTRACER_DECLSPEC Sphere : public Object {
public:
	Sphere() {}

	IntersectResult intersect(const Ray& ray) const override;
};