#include "pch.h"
#include <cmath>
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

/*
Scenario: Rotating a point around the x axis
Given p ← point(0, 1, 0)
And half_quarter ← rotation_x(π / 4)
And full_quarter ← rotation_x(π / 2)
Then half_quarter * p = point(0, √2/2, √2/2)
And full_quarter * p = point(0, 0, 1)
*/
TEST(Transforms, RotateX) {
	auto p = Tuple::CreatePoint(0, 1, 0);
	auto half_quarter = Transforms::MakeRotateX(M_PI / 4);
	auto full_quarter = Transforms::MakeRotateX(M_PI / 2);

	auto expectedHalf = Tuple::CreatePoint(0, sqrt(2) / 2.0, sqrt(2) / 2.0);
	auto expectedFull = Tuple::CreatePoint(0, 0, 1);

	EXPECT_TRUE((half_quarter * p).isEqual(expectedHalf));
	EXPECT_TRUE((full_quarter * p).isEqual(expectedFull));
}

/*
Scenario: The inverse of an x-rotation rotates in the opposite direction
Given p ← point(0, 1, 0)
And half_quarter ← rotation_x(π / 4)
And inv ← inverse(half_quarter)
Then inv * p = point(0, √2/2, -√2/2)
*/
TEST(Transforms, InvRotateX) {
	auto p = Tuple::CreatePoint(0, 1, 0);
	auto half_quarter = Transforms::MakeRotateX(M_PI / 4);
	auto inv = half_quarter.inverse();

	auto expectedHalf = Tuple::CreatePoint(0, sqrt(2) / 2.0, -sqrt(2) / 2.0);

	EXPECT_TRUE((inv * p).isEqual(expectedHalf));
}

/*
Scenario: Rotating a point around the y axis
Given p ← point(0, 0, 1)
And half_quarter ← rotation_y(π / 4)
And full_quarter ← rotation_y(π / 2)
Then half_quarter * p = point(√2/2, 0, √2/2)
And full_quarter * p = point(1, 0, 0)
*/
TEST(Transforms, RotateY) {
	auto p = Tuple::CreatePoint(0, 0, 1);
	auto half_quarter = Transforms::MakeRotateY(M_PI / 4);
	auto full_quarter = Transforms::MakeRotateY(M_PI / 2);

	auto expectedHalf = Tuple::CreatePoint(sqrt(2) / 2.0, 0, sqrt(2) / 2.0);
	auto expectedFull = Tuple::CreatePoint(1, 0, 0);

	EXPECT_TRUE((half_quarter * p).isEqual(expectedHalf));
	EXPECT_TRUE((full_quarter * p).isEqual(expectedFull));
}

/*
Scenario: Rotating a point around the z axis
Given p ← point(0, 1, 0)
And half_quarter ← rotation_z(π / 4)
And full_quarter ← rotation_z(π / 2)
Then half_quarter * p = point(-√2/2, √2/2, 0)
And full_quarter * p = point(-1, 0, 0)
*/
TEST(Transforms, RotateZ) {
	auto p = Tuple::CreatePoint(0, 1, 0);
	auto half_quarter = Transforms::MakeRotateZ(M_PI / 4);
	auto full_quarter = Transforms::MakeRotateZ(M_PI / 2);

	auto expectedHalf = Tuple::CreatePoint(-sqrt(2) / 2.0, sqrt(2) / 2.0, 0);
	auto expectedFull = Tuple::CreatePoint(-1, 0, 0);

	EXPECT_TRUE((half_quarter * p).isEqual(expectedHalf));
	EXPECT_TRUE((full_quarter * p).isEqual(expectedFull));
}

/*
Scenario: A shearing transformation moves x in proportion to y
Given transform ← shearing(1, 0, 0, 0, 0, 0)
And p ← point(2, 3, 4)
Then transform * p = point(5, 3, 4)
*/
TEST(Transforms, ShearXY) {
	auto transform = Transforms::MakeShear(1, 0, 0, 0, 0, 0);
	auto p = Tuple::CreatePoint(2, 3, 4);

	auto expected = Tuple::CreatePoint(5, 3, 4);

	EXPECT_TRUE((transform * p).isEqual(expected));
}

/*
Scenario: A shearing transformation moves x in proportion to z
Given transform ← shearing(0, 1, 0, 0, 0, 0)
And p ← point(2, 3, 4)
Then transform* p = point(6, 3, 4)
*/
TEST(Transforms, ShearXZ) {
	auto transform = Transforms::MakeShear(0, 1, 0, 0, 0, 0);
	auto p = Tuple::CreatePoint(2, 3, 4);

	auto expected = Tuple::CreatePoint(6, 3, 4);

	EXPECT_TRUE((transform * p).isEqual(expected));
}


/*
Scenario: A shearing transformation moves y in proportion to x
Given transform ← shearing(0, 0, 1, 0, 0, 0)
And p ← point(2, 3, 4)
Then transform * p = point(2, 5, 4)
*/
TEST(Transforms, ShearYX) {
	auto transform = Transforms::MakeShear(0, 0, 1, 0, 0, 0);
	auto p = Tuple::CreatePoint(2, 3, 4);

	auto expected = Tuple::CreatePoint(2, 5, 4);

	EXPECT_TRUE((transform * p).isEqual(expected));
}

/*
Scenario: A shearing transformation moves y in proportion to z
Given transform ← shearing(0, 0, 0, 1, 0, 0)
And p ← point(2, 3, 4)
Then transform * p = point(2, 7, 4)
*/
TEST(Transforms, ShearYZ) {
	auto transform = Transforms::MakeShear(0, 0, 0, 1, 0, 0);
	auto p = Tuple::CreatePoint(2, 3, 4);

	auto expected = Tuple::CreatePoint(2, 7, 4);

	EXPECT_TRUE((transform * p).isEqual(expected));
}

/*
Scenario: A shearing transformation moves z in proportion to x
Given transform ← shearing(0, 0, 0, 0, 1, 0)
And p ← point(2, 3, 4)
Then transform * p = point(2, 3, 6)
*/
TEST(Transforms, ShearZX) {
	auto transform = Transforms::MakeShear(0, 0, 0, 0, 1, 0);
	auto p = Tuple::CreatePoint(2, 3, 4);

	auto expected = Tuple::CreatePoint(2, 3, 6);

	EXPECT_TRUE((transform * p).isEqual(expected));
}

/*
Scenario: A shearing transformation moves z in proportion to y
Given transform ← shearing(0, 0, 0, 0, 0, 1)
And p ← point(2, 3, 4)
Then transform * p = point(2, 3, 7)
*/
TEST(Transforms, ShearZY) {
	auto transform = Transforms::MakeShear(0, 0, 0, 0, 0, 1);
	auto p = Tuple::CreatePoint(2, 3, 4);

	auto expected = Tuple::CreatePoint(2, 3, 7);

	EXPECT_TRUE((transform * p).isEqual(expected));
}

/*
Scenario: Individual transformations are applied in sequence
Given p ← point(1, 0, 1)
And A ← rotation_x(π / 2)
And B ← scaling(5, 5, 5)
And C ← translation(10, 5, 7)
# apply rotation first
When p2 ← A * p
Then p2 = point(1, -1, 0)
# then apply scaling
When p3 ← B * p2
Then p3 = point(5, -5, 0)
# then apply translation
When p4 ← C * p3
Then p4 = point(15, 0, 7)
*/
TEST(Transforms, TransformsInSequence) {
	auto p = Tuple::CreatePoint(1, 0, 1);
	auto A = Transforms::MakeRotateX(M_PI / 2);
	auto B = Transforms::MakeScale(5, 5, 5);
	auto C = Transforms::MakeTranslation(10, 5, 7);

	auto p2 = A * p;
	EXPECT_TRUE(p2.isEqual(Tuple::CreatePoint(1, -1, 0)));

	auto p3 = B * p2;
	EXPECT_TRUE(p3.isEqual(Tuple::CreatePoint(5, -5, 0)));

	auto p4 = C * p3;
	EXPECT_TRUE(p4.isEqual(Tuple::CreatePoint(15, 0, 7)));
}

/*Scenario: Chained transformations must be applied in reverse order
Given p ← point(1, 0, 1)
And A ← rotation_x(π / 2)
And B ← scaling(5, 5, 5)
And C ← translation(10, 5, 7)
When T ← C * B * A
Then T * p = point(15, 0, 7)
*/
TEST(Transforms, TransformsChained) {
	auto p = Tuple::CreatePoint(1, 0, 1);
	auto A = Transforms::MakeRotateX(M_PI / 2);
	auto B = Transforms::MakeScale(5, 5, 5);
	auto C = Transforms::MakeTranslation(10, 5, 7);

	auto T = C * B * A;
	EXPECT_TRUE((T * p).isEqual(Tuple::CreatePoint(15, 0, 7)));
}

TEST(Transforms, TransformsFluent) {
	auto p = Tuple::CreatePoint(1, 0, 1);
	auto T = Matrix4().rotateX(M_PI / 2).scale(5, 5, 5).translate(10, 5, 7);

	EXPECT_TRUE((T * p).isEqual(Tuple::CreatePoint(15, 0, 7)));
}