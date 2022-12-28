#pragma once
#include <vector>
#include "Export.h"
#include "Tuple.h"
#include "Intersection.h"

class Object;
template<int, int> class Matrix; 
using Matrix4 = Matrix<4, 4>;

class RAYTRACER_DECLSPEC Ray {
public:
	Tuple m_origin;
	Tuple m_direction;

	Ray(const Tuple& origin, const Tuple& direction) : m_origin(origin), m_direction(direction) {
		_ASSERT(m_origin.isPoint() == true && m_direction.isVector() == true);
	}

	Tuple position(double t) const {
		return m_origin + m_direction * t;
	}

	Intersections intersect(const Object& obj) const;

	Ray transform(const Matrix4& matrix) const;
};