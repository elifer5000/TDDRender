#include "pch.h"
#include <vector>
#include "Utils.h"
#include "Matrix.h"
#include "Tuple.h"

/*
Scenario: Multiplying by a translation matrix
Given transform ← translation(5, -3, 2)
And p ← point(-3, 4, 5)
Then transform * p = point(2, 1, 7)
*/
TEST(Transforms, Translation) {
	auto transform = Transforms::MakeTranslation(5, -3, 2);
	auto p = Tuple::CreatePoint(-3, 4, 5);

	auto expected = Tuple::CreatePoint(2, 1, 7);
	////auto m1= Matrix3().translate(3, 4, 5);
	////auto m = Matrix4::MakeTranslation(4, 5, 6);
	////m.MakeTranslation(6, 7, 8);
	EXPECT_TRUE((transform * p).isEqual(expected));
}

/*
Scenario: Multiplying by the inverse of a translation matrix
Given transform ← translation(5, -3, 2)
And inv ← inverse(transform)
And p ← point(-3, 4, 5)
Then inv * p = point(-8, 7, 3)
*/
TEST(Transforms, InvTranslation) {
	auto transform = Transforms::MakeTranslation(5, -3, 2);
	auto inv = transform.inverse();
	auto p = Tuple::CreatePoint(-3, 4, 5);

	auto expected = Tuple::CreatePoint(-8, 7, 3);

	EXPECT_TRUE((inv * p).isEqual(expected));
}

/*
Scenario: Translation does not affect vectors
Given transform ← translation(5, -3, 2)
And v ← vector(-3, 4, 5) Then transform* v = v
*/
TEST(Transforms, TranslationVector) {
	auto transform = Transforms::MakeTranslation(5, -3, 2);
	auto v = Tuple::CreateVector(-3, 4, 5);
	
	EXPECT_TRUE((transform * v).isEqual(v));
}

/*
Scenario: A scaling matrix applied to a point
Given transform ← scaling(2, 3, 4)
And p ← point(-4, 6, 8)
Then transform * p = point(-8, 18, 32)
*/
TEST(Transforms, ScalingPoint) {
	auto transform = Transforms::MakeScale(2, 3, 4);
	auto p = Tuple::CreatePoint(-4, 6, 8);

	auto expected = Tuple::CreatePoint(-8, 18, 32);

	EXPECT_TRUE((transform * p).isEqual(expected));
}

/*
Scenario: A scaling matrix applied to a vector
Given transform ← scaling(2, 3, 4)
And v ← vector(-4, 6, 8)
Then transform * v = vector(-8, 18, 32)
*/
TEST(Transforms, ScalingVector) {
	auto transform = Transforms::MakeScale(2, 3, 4);
	auto v = Tuple::CreateVector(-4, 6, 8);

	auto expected = Tuple::CreateVector(-8, 18, 32);

	EXPECT_TRUE((transform * v).isEqual(expected));
}

/*
Scenario: Multiplying by the inverse of a scaling matrix
Given transform ← scaling(2, 3, 4)
And inv ← inverse(transform)
And v ← vector(-4, 6, 8)
Then inv * v = vector(-2, 2, 2)
*/
TEST(Transforms, InverseScaling) {
	auto transform = Transforms::MakeScale(2, 3, 4);
	auto inv = transform.inverse();
	auto v = Tuple::CreateVector(-4, 6, 8);

	auto expected = Tuple::CreateVector(-2, 2, 2);

	EXPECT_TRUE((inv * v).isEqual(expected));
}
/*
Scenario: Reflection is scaling by a negative value
Given transform ← scaling(-1, 1, 1)
And p ← point(2, 3, 4)
Then transform * p = point(-2, 3, 4)
*/
TEST(Transforms, Reflection) {
	auto transform = Transforms::MakeScale(-1, 1, 1);
	auto p = Tuple::CreatePoint(2, 3, 4);

	auto expected = Tuple::CreatePoint(-2, 3, 4);

	EXPECT_TRUE((transform * p).isEqual(expected));
}