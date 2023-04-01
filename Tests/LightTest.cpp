#include "pch.h"
#include "Primitives/Sphere.h"

/*
Scenario: The normal on a sphere at a point on the x axis
Given s ← sphere()
When n ← normal_at(s, point(1, 0, 0))
Then n = vector(1, 0, 0)
*/
TEST(Light, SphereNormalX) {
	auto s = Sphere();
	auto n = s.normalAt(Tuple::CreatePoint(1, 0, 0));

	EXPECT_TRUE(n.isEqual(Tuple::CreateVector(1, 0, 0)));
}

/*
Scenario: The normal on a sphere at a point on the y axis
Given s ← sphere()
When n ← normal_at(s, point(0, 1, 0))
Then n = vector(0, 1, 0)
*/
TEST(Light, SphereNormalY) {
	auto s = Sphere();
	auto n = s.normalAt(Tuple::CreatePoint(0, 1, 0));

	EXPECT_TRUE(n.isEqual(Tuple::CreateVector(0, 1, 0)));
}

/*
Scenario: The normal on a sphere at a point on the z axis
Given s ← sphere()
When n ← normal_at(s, point(0, 0, 1))
Then n = vector(0, 0, 1)
*/
TEST(Light, SphereNormalZ) {
	auto s = Sphere();
	auto n = s.normalAt(Tuple::CreatePoint(0, 0, 1));

	EXPECT_TRUE(n.isEqual(Tuple::CreateVector(0, 0, 1)));
}

/*
Scenario: The normal on a sphere at a nonaxial point
Given s ← sphere()
When n ← normal_at(s, point(√3/3, √3/3, √3/3))
Then n = vector(√3/3, √3/3, √3/3)
*/
TEST(Light, SphereNormalNonAxial) {
	auto s = Sphere();
	auto p = sqrt(3) / 3;
	auto n = s.normalAt(Tuple::CreatePoint(p, p, p));

	EXPECT_TRUE(n.isEqual(Tuple::CreateVector(p, p, p)));
}

/*
Scenario: The normal is a normalized vector
Given s ← sphere()
When n ← normal_at(s, point(√3/3, √3/3, √3/3))
Then n = normalize(n)
*/
TEST(Light, NormalIsNormalized) {
	auto s = Sphere();
	auto p = sqrt(3) / 3;
	auto n = s.normalAt(Tuple::CreatePoint(p, p ,p));
	auto n_expected = n;
	n_expected.normalize();

	EXPECT_TRUE(n.isEqual(n_expected));
}

/*
Scenario: Computing the normal on a translated sphere
Given s ← sphere()
And set_transform(s, translation(0, 1, 0))
When n ← normal_at(s, point(0, 1.70711, -0.70711)) 
Then n = vector(0, 0.70711, -0.70711)
*/
TEST(Light, NormalTranslatedSphere) {
	auto s = Sphere();
	s.setTransform(Transforms::MakeTranslation(0, 1, 0));
	
	auto n = s.normalAt(Tuple::CreatePoint(0, 1.70711, -0.70711));

	EXPECT_TRUE(n.isEqual(Tuple::CreateVector(0, 0.70711, -0.70711)));
}

/*
Scenario: Computing the normal on a transformed sphere
Given s ← sphere()
And m ← scaling(1, 0.5, 1) * rotation_z(π/5)
And set_transform(s, m)
When n ← normal_at(s, point(0, √2/2, -√2/2))
Then n = vector(0, 0.97014, -0.24254)
*/
TEST(Light, NormalTransformedSphere) {
	auto s = Sphere();
	s.setTransform(Transforms::MakeScale(1, 0.5, 1) * Transforms::MakeRotateZ(M_PI / 5));

	auto n = s.normalAt(Tuple::CreatePoint(0, sqrt(2) / 2, -sqrt(2) / 2));

	EXPECT_TRUE(n.isEqual(Tuple::CreateVector(0, 0.97014, -0.24254)));
}