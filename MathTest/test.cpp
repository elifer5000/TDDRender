#include "pch.h"
#include "Tuple.h"
#include "Utils.h"

TEST(Utils, Comparisons) {
	EXPECT_TRUE(isEqual(5.0f, 5.000009f));
	EXPECT_FALSE(isEqual(5.0f, 4.8f));
	EXPECT_TRUE(comp(5.f, 3.f) == 1);
	EXPECT_TRUE(comp(3.f, 5.f) == -1);
	EXPECT_TRUE(comp(3.f, 3.000001f) == 0);
	EXPECT_TRUE(comp(3.f, 3.00001f) == -1);
	EXPECT_TRUE(comp(3.f, 2.9999f) == 1);
}
/*Scenario: A tuple with w=1.0 is a point Given a ← tuple(4.3, -4.2, 3.1, 1.0) Then a.x = 4.3
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

/*Scenario: A tuple with w=0 is a vector Given a ← tuple(4.3, -4.2, 3.1, 0.0) Then a.x = 4.3
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
Scenario: point() creates tuples with w = 1 Given p ← point(4, -4, 3)
Then p = tuple(4, -4, 3, 1)
*/
TEST(Tuples, CreatePoint) {
	auto p = Tuple::CreatePoint(4.f, -4.f, 3.f);
	EXPECT_TRUE(p.isPoint());
}
/*
Scenario : vector() creates tuples with w = 0 Given v ← vector(4, -4, 3)
Then v = tuple(4, -4, 3, 0)
*/
TEST(Tuples, CreateVector) {
	auto p = Tuple::CreateVector(4.f, -4.f, 3.f);
	EXPECT_TRUE(p.isVector());
}

/*
Scenario: Adding two tuples Given a1 ← tuple(3, -2, 5, 1) And a2 ← tuple(-2, 3, 1, 0)
Then a1 + a2 = tuple(1, 1, 6, 1)
*/
TEST(Tuples, AddTuples) {

}