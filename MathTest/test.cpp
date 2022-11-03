#include "pch.h"
#include "Tuple.h"
#include "Utils.h"

TEST(Utils, Comparisons) {
	EXPECT_TRUE(isEqualf(5.0f, 5.000009f));
	EXPECT_FALSE(isEqualf(5.0f, 4.8f));
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
	EXPECT_EQ(a.x, 4.3f);
	EXPECT_EQ(a.y, -4.2f);
	EXPECT_EQ(a.z, 3.1f);
	EXPECT_EQ(a.w, 1.0f);
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
	EXPECT_EQ(a.x, 4.3f);
	EXPECT_EQ(a.y, -4.2f);
	EXPECT_EQ(a.z, 3.1f);
	EXPECT_EQ(a.w, 0.0f);
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
	Tuple a = Tuple(1.f, -2.f, 3.f, -4.f);

	a.negate();
	Tuple expected = Tuple(-1.f, 2.f, -3.f, 4.f);
	EXPECT_TRUE(a.isEqual(expected));
}