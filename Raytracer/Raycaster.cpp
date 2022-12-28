#include "pch.h"
#include "Raycaster.h"
#include "Primitives/Object.h"
#include "Matrix.h"

Intersections Ray::intersect(const Object& obj) const {
	return obj.intersect(*this);
}

Ray Ray::transform(const Matrix4& matrix) const {
	auto newOrigin = matrix * m_origin;
	auto newDirection = matrix * m_direction;

	return Ray(newOrigin, newDirection);
}