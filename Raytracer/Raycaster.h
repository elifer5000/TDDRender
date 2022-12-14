#pragma once
#include "Tuple.h"

class Ray {
public:
	Tuple origin;
	Tuple direction;

	Ray(const Tuple& _origin, const Tuple& _direction) : origin(_origin), direction(_direction) {}

	Tuple position(double t) const {
		return origin + direction * t;
	}
};