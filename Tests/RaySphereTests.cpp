#include "pch.h"
#include "Raycaster.h"
#include "Utils.h"
#include "Primitives/Sphere.h"
#include "Intersection.h"

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
	EXPECT_EQ(xs.count(), 2);
	EXPECT_TRUE(isEquald(xs[0].m_t, 4.0));
	EXPECT_TRUE(isEquald(xs[1].m_t, 6.0));
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
	EXPECT_EQ(xs.count(), 2);
	EXPECT_TRUE(isEquald(xs[0].m_t, 5.0));
	EXPECT_TRUE(isEquald(xs[1].m_t, 5.0));
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
	EXPECT_EQ(xs.count(), 0);
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
	EXPECT_EQ(xs.count(), 2);
	EXPECT_TRUE(isEquald(xs[0].m_t, -1.0));
	EXPECT_TRUE(isEquald(xs[1].m_t, 1.0));
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
	EXPECT_EQ(xs.count(), 2);
	EXPECT_TRUE(isEquald(xs[0].m_t, -6.0));
	EXPECT_TRUE(isEquald(xs[1].m_t, -4.0));
}

/*
Scenario: An intersection encapsulates t and object
Given s ← sphere()
When i ← intersection(3.5, s)
Then i.t = 3.5
And i.object = s
*/
TEST(Raysphere, IntersectionClass) {
	auto sphere = Sphere();
	auto i = Intersection{ 3.5, &sphere };
	EXPECT_EQ(i.m_t, 3.5);
	EXPECT_EQ(&sphere, i.m_object);
}

/*
Scenario: Aggregating intersections Given s ← sphere()
And i1 ← intersection(1, s)
And i2 ← intersection(2, s)
When xs ← intersections(i1, i2)
Then xs.count = 2
And xs[0].t = 1
And xs[1].t = 2
*/
TEST(Raysphere, IntersectionAggregate) {
	auto sphere = Sphere();
	auto i1 = Intersection{ 1, &sphere };
	auto i2 = Intersection{ 2, &sphere };

	auto intersections = Intersections({ i1, i2 });
	EXPECT_EQ(intersections.count(), 2);

	auto first = intersections.get(0);
	EXPECT_TRUE(first);
	EXPECT_EQ(first->m_t, 1);

	auto second = intersections.get(1);
	EXPECT_TRUE(second);
	EXPECT_EQ(second->m_t, 2);
}

/*
Scenario: Intersect sets the object on the intersection 
Given r ← ray(point(0, 0, -5), vector(0, 0, 1))
And s ← sphere()
When xs ← intersect(s, r)
Then xs.count = 2
And xs[0].object = s 
And xs[1].object = s
*/
TEST(Raysphere, IntersecSetsObject) {
	auto origin = Tuple::CreatePoint(0, 0, -5);
	auto direction = Tuple::CreateVector(0, 0, 1);
	auto ray = Ray(origin, direction);

	auto sphere = Sphere();
	auto xs = ray.intersect(sphere);

	EXPECT_EQ(xs.count(), 2);
	EXPECT_EQ(xs[0].m_object, &sphere);
	EXPECT_EQ(xs[1].m_object, &sphere);
}

/*
Scenario: The hit, when all intersections have positive t
Given s ← sphere()
And i1 ← intersection(1, s)
And i2 ← intersection(2, s)
And xs ← intersections(i2, i1)
When i ← hit(xs) Then i = i1
*/
TEST(Raysphere, HitAllPositive) {
	auto sphere = Sphere();
	
	auto i1 = Intersection{ 1, &sphere };
	auto i2 = Intersection{ 2, &sphere };

	auto xs = Intersections({ i2, i1 });
	auto i = xs.hit();
	EXPECT_EQ(i.value(), i1);
}

/*
Scenario: The hit, when some intersections have negative t
Given s ← sphere()
And i1 ← intersection(-1, s)
And i2 ← intersection(1, s) 
And xs ← intersections(i2, i1)
When i ← hit(xs) Then i = i2
*/
TEST(Raysphere, HitSomeNegative) {
	auto sphere = Sphere();

	auto i1 = Intersection{ -1, &sphere };
	auto i2 = Intersection{ 1, &sphere };

	auto xs = Intersections({ i2, i1 });
	auto i = xs.hit();
	EXPECT_EQ(i.value(), i2);
}

/*
Scenario: The hit, when all intersections have negative t
Given s ← sphere()
And i1 ← intersection(-2, s)
And i2 ← intersection(-1, s)
And xs ← intersections(i2, i1)
When i ← hit(xs)
Then i is nothing
*/
TEST(Raysphere, HitAllNegative) {
	auto sphere = Sphere();

	auto i1 = Intersection{ -2, &sphere };
	auto i2 = Intersection{ -1, &sphere };

	auto xs = Intersections({ i2, i1 });
	auto i = xs.hit();
	EXPECT_FALSE(i);
}

/*
Scenario: The hit is always the lowest nonnegative intersection
Given s ← sphere()
And i1 ← intersection(5, s)
And i2 ← intersection(7, s)
And i3 ← intersection(-3, s)
And i4 ← intersection(2, s)
And xs ← intersections(i1, i2, i3, i4)
When i ← hit(xs) Then i = i4
*/
TEST(Raysphere, HitLowestNonnegative) {
	auto sphere = Sphere();

	auto i1 = Intersection{ 5, &sphere };
	auto i2 = Intersection{ 7, &sphere };
	auto i3 = Intersection{ -3, &sphere };
	auto i4 = Intersection{ 2, &sphere };

	auto xs = Intersections({ i1, i2, i3, i4 });
	auto i = xs.hit();
	EXPECT_EQ(i.value(), i4);

}