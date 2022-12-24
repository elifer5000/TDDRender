#include "pch.h"
#include "Sphere.h"

IntersectResult Sphere::intersect(const Ray& ray) const {
	// Vector from sphere center to ray origin
	auto sphereToRayVec = ray.m_origin - Tuple::CreatePoint(0, 0, 0);
	auto a = ray.m_direction.dot(ray.m_direction);
	auto b = 2 * ray.m_direction.dot(sphereToRayVec);
	auto c = sphereToRayVec.dot(sphereToRayVec) - 1;

	auto discriminant = b * b - 4 * a * c;

	if (discriminant < 0) {
		return IntersectResult();
	}

	discriminant = sqrt(discriminant);

	auto t1 = (-b - discriminant) / (2 * a);
	auto t2 = (-b + discriminant) / (2 * a);

	return IntersectResult{ t1, t2 };
}