#include "pch.h"
#include "Raycaster.h"
//#include <cmath>
//#include <vector>

#include "Utils.h"
#include "Primitives/Sphere.h"
//#include "Matrix.h"
//#include "Tuple.h"

/*
Sceneario: Creating 2 spheres
Given s1 ← sphere()
And s2 ← sphere()
Then s1.id = 1
And s2.id = 2
*/
TEST(Raysphere, SpheresId) {
	auto s1 = Sphere();
	auto s2 = Sphere();

	EXPECT_EQ(s1.id(), 0);
	EXPECT_EQ(s2.id(), 1);
}

/*
Scenario: Creating and querying a ray
Given origin ← point(1, 2, 3)
And direction ← vector(4, 5, 6)
When r ← ray(origin, direction) Then r.origin = origin
And r.direction = direction
*/
TEST(Raysphere, CreateRay) {
	auto origin = Tuple::CreatePoint(1, 2, 3);
	auto direction = Tuple::CreateVector(4, 5, 6);
	auto ray = Ray(origin, direction);

	EXPECT_TRUE(ray.m_origin.isEqual(origin));
	EXPECT_TRUE(ray.m_origin.isPoint());
	EXPECT_TRUE(ray.m_direction.isEqual(direction));
	EXPECT_TRUE(ray.m_direction.isVector());


}

/*
Scenario: Computing a point from a distance
Given r ← ray(point(2, 3, 4), vector(1, 0, 0))
Then position(r, 0) = point(2, 3, 4)
And position(r, 1) = point(3, 3, 4)
And position(r, -1) = point(1, 3, 4)
And position(r, 2.5) = point(4.5, 3, 4)
*/
TEST(Raysphere, ComputePointFromDistance) {
	auto origin = Tuple::CreatePoint(2, 3, 4);
	auto direction = Tuple::CreateVector(1, 0, 0);
	auto ray = Ray(origin, direction);

	EXPECT_TRUE(ray.position(0).isEqual(Tuple::CreatePoint(2, 3, 4)));
	EXPECT_TRUE(ray.position(1).isEqual(Tuple::CreatePoint(3, 3, 4)));
	EXPECT_TRUE(ray.position(-1).isEqual(Tuple::CreatePoint(1, 3, 4)));
	EXPECT_TRUE(ray.position(2.5).isEqual(Tuple::CreatePoint(4.5, 3, 4)));
}

/*
Scenario: A ray intersects a sphere at two points
Given r ← ray(point(0, 0, -5), vector(0, 0, 1))
And s ← sphere()
When xs ← intersect(s, r)
Then xs.count = 2
And xs[0] = 4.0
And xs[1] = 6.0
*/
TEST(Raysphere, RaySphereAt2Points) {
	auto origin = Tuple::CreatePoint(0, 0, -5);
	auto direction = Tuple::CreateVector(0, 0, 1);
	auto ray = Ray(origin, direction);

	auto sphere = Sphere();
	auto xs = ray.intersect(sphere);
	EXPECT_EQ(xs.size(), 2);
	EXPECT_TRUE(isEquald(xs[0], 4.0));
	EXPECT_TRUE(isEquald(xs[1], 6.0));
}

/*
Scenario: A ray intersects a sphere at a tangent
Given r ← ray(point(0, 1, -5), vector(0, 0, 1))
And s ← sphere()
When xs ← intersect(s, r)
Then xs.count = 2
And xs[0] = 5.0
And xs[1] = 5.0
*/
TEST(Raysphere, RaySphereAtTangent) {
	auto origin = Tuple::CreatePoint(0, 1, -5);
	auto direction = Tuple::CreateVector(0, 0, 1);
	auto ray = Ray(origin, direction);

	auto sphere = Sphere();
	auto xs = ray.intersect(sphere);
	EXPECT_EQ(xs.size(), 2);
	EXPECT_TRUE(isEquald(xs[0], 5.0));
	EXPECT_TRUE(isEquald(xs[1], 5.0));
}

/*
Scenario: A ray misses a sphere
Given r ← ray(point(0, 2, -5), vector(0, 0, 1))
And s ← sphere()
When xs ← intersect(s, r)
Then xs.count = 0
*/
TEST(Raysphere, RaySphereMiss) {
	auto origin = Tuple::CreatePoint(0, 2, -5);
	auto direction = Tuple::CreateVector(0, 0, 1);
	auto ray = Ray(origin, direction);

	auto sphere = Sphere();
	auto xs = ray.intersect(sphere);
	EXPECT_EQ(xs.size(), 0);
}

/*
Scenario: A ray originates inside a sphere
Given r ← ray(point(0, 0, 0), vector(0, 0, 1))
And s ← sphere()
When xs ← intersect(s, r)
Then xs.count = 2
And xs[0] = -1.0
And xs[1] = 1.0
*/
TEST(Raysphere, RayInsideSphere) {
	auto origin = Tuple::CreatePoint(0, 0, 0);
	auto direction = Tuple::CreateVector(0, 0, 1);
	auto ray = Ray(origin, direction);

	auto sphere = Sphere();
	auto xs = ray.intersect(sphere);
	EXPECT_EQ(xs.size(), 2);
	EXPECT_TRUE(isEquald(xs[0], -1.0));
	EXPECT_TRUE(isEquald(xs[1], 1.0));
}

/*
Scenario: A sphere is behind a ray
Given r ← ray(point(0, 0, 5), vector(0, 0, 1))
And s ← sphere()
When xs ← intersect(s, r)
Then xs.count = 2
And xs[0] = -6.0
And xs[1] = -4.0
*/
TEST(Raysphere, RayInFrontSphere) {
	auto origin = Tuple::CreatePoint(0, 0, 5);
	auto direction = Tuple::CreateVector(0, 0, 1);
	auto ray = Ray(origin, direction);

	auto sphere = Sphere();
	auto xs = ray.intersect(sphere);
	EXPECT_EQ(xs.size(), 2);
	EXPECT_TRUE(isEquald(xs[0], -6.0));
	EXPECT_TRUE(isEquald(xs[1], -4.0));
}