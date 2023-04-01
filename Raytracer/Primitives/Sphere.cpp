#include "pch.h"
#include "Sphere.h"
#include <vector>

Intersections Sphere::intersect(const Ray& ray) const {
	// Instead of transforming the sphere, we inverse transform the ray, since it's equivalent
	//TODO: See if this should be generalized for all objects (Maybe done in Intersection.cpp)
	auto invRay = ray.transform(m_transform.inverse());
	// Vector from sphere center to ray origin
	auto sphereToRayVec = invRay.m_origin - Tuple::CreatePoint(0, 0, 0);
	auto a = invRay.m_direction.dot(invRay.m_direction);
	auto b = 2 * invRay.m_direction.dot(sphereToRayVec);
	auto c = sphereToRayVec.dot(sphereToRayVec) - 1;

	auto discriminant = b * b - 4 * a * c;

	if (discriminant < 0) {
		return Intersections();
	}

	discriminant = sqrt(discriminant);

	auto t1 = (-b - discriminant) / (2 * a);
	auto t2 = (-b + discriminant) / (2 * a);

	return Intersections({ { t1, this }, { t2, this } });
}

Tuple Sphere::normalAt(const Tuple& point) const {
	Matrix4 inverse = getTransform().inverse();
	auto objectPoint = inverse * point;
	auto normal = objectPoint - Tuple::CreatePoint();
	auto worldNormal = inverse.transpose() * normal;
	worldNormal.w() = 0;
	return worldNormal.normalize();
}