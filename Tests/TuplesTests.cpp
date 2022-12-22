#include "pch.h"
#include "Tuple.h"
#include "Utils.h"

TEST(Utils, Comparisons) {
	EXPECT_TRUE(isEquald(5.0f, 5.000009f));
	EXPECT_FALSE(isEquald(5.0f, 4.8f));
	EXPECT_TRUE(comp(5.f, 3.f) == 1);
	EXPECT_TRUE(comp(3.f, 5.f) == -1);
	EXPECT_TRUE(comp(3.f, 3.000001f) == 0);
	EXPECT_TRUE(comp(3.f, 3.00001f) == -1);
	EXPECT_TRUE(comp(3.f, 2.9999f) == 1);
}
/*Scenario: A tuple with w=1.0 is a point
Given a ← tuple(4.3, -4.2, 3.1, 1.0)
Then a.x = 4.3
And a.y = -4.2
And a.z = 3.1
And a.w = 1.0
And a is a point
And a is not a vector*/
TEST(Tuples, TuplePoint) {
	Tuple a(4.3f, -4.2f, 3.1f, 1.0f);
	EXPECT_EQ(a.x(), 4.3f);
	EXPECT_EQ(a.y(), -4.2f);
	EXPECT_EQ(a.z(), 3.1f);
	EXPECT_EQ(a.w(), 1.0f);
	EXPECT_TRUE(a.isPoint());
	EXPECT_FALSE(a.isVector());
}

/*Scenario: A tuple with w=0 is a vector
Given a ← tuple(4.3, -4.2, 3.1, 0.0)
Then a.x = 4.3
And a.y = -4.2
And a.z = 3.1
And a.w = 0.0
And a is not a point And a is a vector*/
TEST(Tuples, TupleVector) {
	Tuple a(4.3f, -4.2f, 3.1f, 0.0f);
	EXPECT_EQ(a.x(), 4.3f);
	EXPECT_EQ(a.y(), -4.2f);
	EXPECT_EQ(a.z(), 3.1f);
	EXPECT_EQ(a.w(), 0.0f);
	EXPECT_FALSE(a.isPoint());
	EXPECT_TRUE(a.isVector());
}

/*
Scenario: point() creates tuples with w = 1
Given p ← point(4, -4, 3)
Then p = tuple(4, -4, 3, 1)
*/
TEST(Tuples, CreatePoint) {
	auto p = Tuple::CreatePoint(4.f, -4.f, 3.f);
	EXPECT_TRUE(p.isPoint());
}
/*
Scenario : vector() creates tuples with w = 0
Given v ← vector(4, -4, 3)
Then v = tuple(4, -4, 3, 0)
*/
TEST(Tuples, CreateVector) {
	auto p = Tuple::CreateVector(4.f, -4.f, 3.f);
	EXPECT_TRUE(p.isVector());
}

/*
Scenario: Adding two tuples
Given a1 ← tuple(3, -2, 5, 1)
And a2 ← tuple(-2, 3, 1, 0)
Then a1 + a2 = tuple(1, 1, 6, 1)
*/
TEST(Tuples, AddTuples) {
	Tuple a1(3.f, -2.f, 5.f, 1.f);
	Tuple a2(-2.f, 3.f, 1.f, 0.f);

	auto res = a1 + a2;
	Tuple expected(1.f, 1.f, 6.f, 1.f);
	EXPECT_TRUE(res.isEqual(expected));
	EXPECT_TRUE(res.isPoint());
}

/*
Scenario: Subtracting two points
Given p1 ← point(3, 2, 1)
And p2 ← point(5, 6, 7)
Then p1 - p2 = vector(-2, -4, -6)
*/
TEST(Tuples, SubstractPoints) {
	Tuple p1 = Tuple::CreatePoint(3.f, 2.f, 1.f);
	Tuple p2 = Tuple::CreatePoint(5.f, 6.f, 7.f);

	auto res = p1 - p2;
	Tuple expected = Tuple::CreateVector(-2.f, -4.f, -6.f);
	EXPECT_TRUE(res.isEqual(expected));
	EXPECT_TRUE(res.isVector());
}

/*
Scenario: Subtracting a vector from a point
Given p ← point(3, 2, 1)
And v ← vector(5, 6, 7)
Then p - v = point(-2, -4, -6)
*/
TEST(Tuples, SubstractVectorFromPoint) {
	Tuple p = Tuple::CreatePoint(3.f, 2.f, 1.f);
	Tuple v = Tuple::CreateVector(5.f, 6.f, 7.f);

	auto res = p - v;
	Tuple expected = Tuple::CreatePoint(-2.f, -4.f, -6.f);
	EXPECT_TRUE(res.isEqual(expected));
	EXPECT_TRUE(res.isPoint());
}

/*
Scenario: Subtracting two vectors
Given v1 ← vector(3, 2, 1)
And v2 ← vector(5, 6, 7)
Then v1 - v2 = vector(-2, -4, -6)
*/
TEST(Tuples, SubstractVectors) {
	Tuple v1 = Tuple::CreateVector(3.f, 2.f, 1.f);
	Tuple v2 = Tuple::CreateVector(5.f, 6.f, 7.f);

	auto res = v1 - v2;
	Tuple expected = Tuple::CreateVector(-2.f, -4.f, -6.f);
	EXPECT_TRUE(res.isEqual(expected));
	EXPECT_TRUE(res.isVector());
}

/*
Scenario: Subtracting a vector from the zero vector
Given zero ← vector(0, 0, 0)
And v ← vector(1, -2, 3)
Then zero - v = vector(-1, 2, -3)
*/
TEST(Tuples, SubstractVectorFromZeroVector) {
	Tuple zero = Tuple::CreateVector(0.f, 0.f, 0.f);
	Tuple v = Tuple::CreateVector(1.f, -2.f, 3.f);

	auto res = zero - v;
	Tuple expected = Tuple::CreateVector(-1.f, 2.f, -3.f);
	EXPECT_TRUE(res.isEqual(expected));
}

/*
Scenario: Negating a tuple
Given a ← tuple(1, -2, 3, -4)
Then -a = tuple(-1, 2, -3, 4)
*/
TEST(Tuples, NegateTuple) {
	Tuple a(1.f, -2.f, 3.f, -4.f);

	a.negate();
	Tuple expected = Tuple(-1.f, 2.f, -3.f, 4.f);
	EXPECT_TRUE(a.isEqual(expected));
}

TEST(Tuples, NegateTupleNonMutating) {
	Tuple a(1.f, -2.f, 3.f, -4.f);
	Tuple original(a);

	Tuple b = -a;
	Tuple expected = Tuple(-1.f, 2.f, -3.f, 4.f);
	EXPECT_TRUE(b.isEqual(expected));
	EXPECT_TRUE(a.isEqual(original)); // a remains unchanged
}

/*
Scenario: Multiplying a tuple by a scalar
Given a ← tuple(1, -2, 3, -4)
Then a * 3.5 = tuple(3.5, -7, 10.5, -14)
*/
TEST(Tuples, MultiplyScalar) {
	Tuple a(1.f, -2.f, 3.f, -4.f);

	Tuple res = a * 3.5f;
	Tuple expected = Tuple(3.5f, -7.f, 10.5f, -14.f);
	EXPECT_TRUE(res.isEqual(expected));
}


/*
Scenario: Multiplying a tuple by a fraction
Given a ← tuple(1, -2, 3, -4)
Then a * 0.5 = tuple(0.5, -1, 1.5, -2)
*/
TEST(Tuples, MultiplyScalarFraction) {
	Tuple a(1.f, -2.f, 3.f, -4.f);

	Tuple res = a * 0.5f;
	Tuple expected = Tuple(0.5f, -1.f, 1.5f, -2.f);
	EXPECT_TRUE(res.isEqual(expected));
}

/*
Scenario: Dividing a tuple by a scalar
Given a ← tuple(1, -2, 3, -4)
Then a / 2 = tuple(0.5, -1, 1.5, -2)
*/
TEST(Tuples, DivideScalarFraction) {
	Tuple a(1.f, -2.f, 3.f, -4.f);

	Tuple res = a / 2.f;
	Tuple expected = Tuple(0.5f, -1.f, 1.5f, -2.f);
	EXPECT_TRUE(res.isEqual(expected));
}

/*
Scenario: Computing the magnitude of vector(1, 0, 0)
Given v ← vector(1, 0, 0)
Then magnitude(v) = 1
*/
TEST(Tuples, Magnitude1) {
	Tuple v = Tuple::CreateVector(1.f, 0.f, 0.f);
	EXPECT_TRUE(isEquald(v.magnitude(), 1.f));
}

/*
Scenario: Computing the magnitude of vector(0, 1, 0)
Given v ← vector(0, 1, 0)
Then magnitude(v) = 1
*/
TEST(Tuples, Magnitude2) {
	Tuple v = Tuple::CreateVector(0.f, 1.f, 0.f);
	EXPECT_TRUE(isEquald(v.magnitude(), 1.f));
}


/*
Scenario: Computing the magnitude of vector(0, 0, 1)
Given v ← vector(0, 0, 1)
Then magnitude(v) = 1
*/
TEST(Tuples, Magnitude3) {
	Tuple v = Tuple::CreateVector(0.f, 0.f, 1.f);
	EXPECT_TRUE(isEquald(v.magnitude(), 1.f));
}


/*
Scenario: Computing the magnitude of vector(1, 2, 3)
Given v ← vector(1, 2, 3)
Then magnitude(v) = √14
*/
TEST(Tuples, Magnitude4) {
	Tuple v = Tuple::CreateVector(1.f, 2.f, 3.f);
	EXPECT_TRUE(isEquald(v.magnitude(), sqrt(14.f)));
}


/*
Scenario: Computing the magnitude of vector(-1, -2, -3)
Given v ← vector(-1, -2, -3)
Then magnitude(v) = √14
*/
TEST(Tuples, Magnitude5) {
	Tuple v = Tuple::CreateVector(-1.f, -2.f, -3.f);
	EXPECT_TRUE(isEquald(v.magnitude(), sqrt(14.f)));
}

/*
Scenario: Normalizing vector(4, 0, 0) gives (1, 0, 0)
Given v ← vector(4, 0, 0)
Then normalize(v) = vector(1, 0, 0)
*/
TEST(Tuples, Normalize1) {
	Tuple v = Tuple::CreateVector(4.f, 0.f, 0.f);

	Tuple expected = Tuple::CreateVector(1.f, 0.f, 0.f);
	EXPECT_TRUE(v.normalize().isEqual(expected));
}

/*
Scenario: Normalizing vector(1, 2, 3)
Given v ← vector(1, 2, 3)
Then normalize(v) = approximately vector(0.26726, 0.53452, 0.80178)
*/
TEST(Tuples, Normalize2) {
	Tuple v = Tuple::CreateVector(1.f, 2.f, 3.f);

	Tuple expected = Tuple::CreateVector(0.26726f, 0.53452f, 0.80178f);
	EXPECT_TRUE(v.normalize().isEqual(expected));
}

/*
Scenario: The magnitude of a normalized vector
Given v ← vector(1, 2, 3)
When norm ← normalize(v)
Then magnitude(norm) = 1
*/
TEST(Tuples, Normalize3) {
	Tuple v = Tuple::CreateVector(4.f, 0.f, 0.f);
	
	EXPECT_TRUE(isEquald(v.normalize().magnitude(), 1.f));
}

/*
Scenario: The dot product of two tuples
Given a ← vector(1, 2, 3)
And b ← vector(2, 3, 4)
Then dot(a, b) = 20
*/
TEST(Tuples, DotProduct) {
	Tuple a = Tuple::CreateVector(1.f, 2.f, 3.f);
	Tuple b = Tuple::CreateVector(2.f, 3.f, 4.f);

	EXPECT_TRUE(isEquald(a.dot(b), 20.f));
}

/*
Scenario: The cross product of two vectors
Given a ← vector(1, 2, 3)
And b ← vector(2, 3, 4)
Then cross(a, b) = vector(-1, 2, -1)
And cross(b, a) = vector(1, -2, 1)
*/
TEST(Tuples, CrossProduct) {
	Tuple a = Tuple::CreateVector(1.f, 2.f, 3.f);
	Tuple b = Tuple::CreateVector(2.f, 3.f, 4.f);

	Tuple expected = Tuple::CreateVector(-1.f, 2.f, -1.f);
	EXPECT_TRUE(a.cross(b).isEqual(expected));
	
	Tuple expectedOpposite = Tuple::CreateVector(1.f, -2.f, 1.f);
	EXPECT_TRUE(b.cross(a).isEqual(expectedOpposite));
}