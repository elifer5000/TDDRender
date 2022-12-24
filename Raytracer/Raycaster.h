#pragma once
#include <vector>
#include "Export.h"
#include "Tuple.h"

class Object;

using IntersectResult = std::vector<double>;

class RAYTRACER_DECLSPEC Ray {
public:
	Tuple m_origin;
	Tuple m_direction;

	Ray(const Tuple& origin, const Tuple& direction) : m_origin(origin), m_direction(direction) {}

	Tuple position(double t) const {
		return m_origin + m_direction * t;
	}

	IntersectResult intersect(const Object& obj) const;
};