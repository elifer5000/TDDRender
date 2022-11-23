﻿#include "pch.h"
#include <vector>
#include "Utils.h"
#include "Matrix.h"
#include "Tuple.h"


/*
Scenario: Constructing and inspecting a 4x4 matrix
Given the following 4x4 matrix M:
|  1 |  2 |  3 |  4 | 
| 5.5| 6.5| 7.5| 8.5| 
| 9  | 10 | 11 | 12 | 
|13.5|14.5|15.5|16.5|
Then M[0,0] = 1
And M[0,3] = 4
And M[1,0] = 5.5
And M[1,2] = 7.5
And M[2,2] = 11
And M[3,0] = 13.5
And M[3,2] = 15.5
*/
TEST(Matrices, Create4x4) {
	Matrix M = Matrix4();

	InitVector data{
		{ 1, 2, 3, 4 },
		{ 5.5, 6.5, 7.5, 8.5 },
		{ 9, 10, 11, 12 },
		{ 13.5, 14.5, 15.5, 16.5 }
	};

	M.initFromData(data);

	EXPECT_DOUBLE_EQ(M.at(0, 0), 1);
	EXPECT_DOUBLE_EQ(M.at(0, 3), 4);
	EXPECT_DOUBLE_EQ(M.at(1, 0), 5.5);
	EXPECT_DOUBLE_EQ(M.at(1, 2), 7.5);
	EXPECT_DOUBLE_EQ(M.at(2, 2), 11);
	EXPECT_DOUBLE_EQ(M.at(3, 0), 13.5);
	EXPECT_DOUBLE_EQ(M.at(3, 2), 15.5);
	
}

/*
Scenario: A 2x2 matrix ought to be representable
Given the following 2x2 matrix M:
| -3 | 5 |
| 1  | -2|
Then M[0,0] = -3
And M[0,1] = 5
And M[1,0] = 1
And M[1,1] = -2
*/
TEST(Matrices, Create2x2) {
	InitVector data{
		{ -3, 5 },
		{ 1, -2 }
	};
	Matrix M = Matrix2(data);

	EXPECT_DOUBLE_EQ(M.at(0, 0), -3);
	EXPECT_DOUBLE_EQ(M.at(0, 1), 5);
	EXPECT_DOUBLE_EQ(M.at(1, 0), 1);
	EXPECT_DOUBLE_EQ(M.at(1, 1), -2);
}

/*
Scenario: A 3x3 matrix ought to be representable
Given the following 3x3 matrix M :
|-3| 5| 0|
| 1|-2|-7| 
|0 | 1| 1|
Then M[0,0] = -3 
And M[1,1] = -2
And M[2,2] = 1
*/
TEST(Matrices, Create3x3) {
	InitVector data{
		{ -3, 5, 0 },
		{ 1, -2, -7 },
		{ 0, 1, 1 }
	};
	Matrix M = Matrix3(data);

	EXPECT_DOUBLE_EQ(M.at(0, 0), -3);
	EXPECT_DOUBLE_EQ(M.at(1, 1), -2);
	EXPECT_DOUBLE_EQ(M.at(2, 2), 1);
}

/*
Scenario: Matrix equality with identical matrices
Given the following matrix A:
|1|2|3|4|
|5|6|7|8|
|9|8|7|6|
|5|4|3|2|
And the following matrix B:
|1|2|3|4|
|5|6|7|8| 
|9|8|7|6| 
|5|4|3|2|
Then A = B
*/
TEST(Matrices, MatrixEquality) {
	InitVector data{
		{ 1, 2, 3, 4 },
		{ 5, 6, 7, 8 },
		{ 9, 8, 7, 6 },
		{ 5, 4, 3, 2 }
	};
	Matrix A = Matrix4(data);

	Matrix B = Matrix4(data);
	
	EXPECT_TRUE(A.isEqual(B));
}

/*
Scenario: Matrix equality with different matrices 
Given the following matrix A:
|1|2|3|4
|5|6|7|8|
|9|8|7|6|
|5|4|3|2|
And the following matrix B:
|2|3|4|5|
|6|7|8|9|
|8|7|6|5|
|4|3|2|1|
Then A != B
*/
TEST(Matrices, MatrixEquality2) {
	InitVector data{
		{ 1, 2, 3, 4 },
		{ 5, 6, 7, 8 },
		{ 9, 8, 7, 6 },
		{ 5, 4, 3, 2 }
	};
	Matrix A = Matrix4(data);
	
	InitVector data2{
	{ 2, 3, 4, 5 },
	{ 6, 7, 8, 9 },
	{ 8, 7, 6, 5 },
	{ 4, 3, 2, 1 }
	};
	Matrix B = Matrix4(data2);
	
	EXPECT_FALSE(A.isEqual(B));
}

/*
Scenario: Multiplying two matrices
Given the following matrix A:
|1|2|3|4|
|5|6|7|8|
|9|8|7|6|
|5|4|3|2|
And the following matrix B:
|-2|1|2| 3|
| 3|2|1|-1|
| 4|3|6| 5|
| 1|2|7| 8|
Then A * B is the following 4x4 matrix:
|20| 22| 50| 48|
|44| 54|114|108|
|40| 58|110|102|
|16| 26| 46| 42|
*/
TEST(Matrices, MatrixMult) {
	InitVector data{
		{ 1, 2, 3, 4 },
		{ 5, 6, 7, 8 },
		{ 9, 8, 7, 6 },
		{ 5, 4, 3, 2 }
	};
	Matrix A = Matrix4(data);

	InitVector data2{
		{ -2, 1, 2, 3 },
		{ 3, 2, 1, -1 },
		{ 4, 3, 6, 5 },
		{ 1, 2, 7, 8 }
	};
	Matrix B = Matrix4(data2);

	InitVector data3{
		{ 20, 22, 50, 48 },
		{ 44, 54, 114, 108 },
		{ 40, 58, 110, 102 },
		{ 16, 26, 46, 42 }
	};
	Matrix expected = Matrix4(data3);

	EXPECT_TRUE((A * B).isEqual(expected));
}

/*
Scenario: A matrix multiplied by a tuple
Given the following matrix A:
|1|2|3|4|
|2|4|4|2|
|8|6|4|1|
|0|0|0|1|
And b ← tuple(1, 2, 3, 1)
Then A * b = tuple(18, 24, 33, 1)
*/
TEST(Matrices, MatrixTupleMult) {
	InitVector data{
		{ 1, 2, 3, 4 },
		{ 2, 4, 4, 2 },
		{ 8, 6, 4, 1 },
		{ 0, 0, 0, 1 }
	};
	Matrix A = Matrix4(data);

	auto b = Tuple(1, 2, 3, 1);

	auto expected = Tuple(18, 24, 33, 1);

	EXPECT_TRUE((A * b).isEqual(expected));
}