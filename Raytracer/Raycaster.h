#pragma once
#include <vector>
#include "Export.h"
#include "Tuple.h"
#include "Intersection.h"

class Object;

class RAYTRACER_DECLSPEC Ray {
public:
	Tuple m_origin;
	Tuple m_direction;

	Ray(const Tuple& origin, const Tuple& direction) : m_origin(origin), m_direction(direction) {}

	Tuple position(double t) const {
		return m_origin + m_direction * t;
	}

	Intersections intersect(const Object& obj) const;
};