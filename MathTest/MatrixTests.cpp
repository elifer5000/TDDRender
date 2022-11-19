#include "pch.h"
#include <vector>
#include "Utils.h"
#include "Matrix.h"


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
	Matrix M = Matrix::Make4x4();

	std::vector<std::vector<double>> data{
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
	Matrix M = Matrix::Make2x2();

	std::vector<std::vector<double>> data{
		{ -3, 5 },
		{ 1, -2 }
	};

	M.initFromData(data);

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
	Matrix M = Matrix::Make3x3();

	std::vector<std::vector<double>> data{
		{ -3, 5, 0 },
		{ 1, -2, -7 },
		{ 0, 1, 1 }
	};

	M.initFromData(data);

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
	Matrix A = Matrix::Make4x4();

	std::vector<std::vector<double>> data{
		{ 1, 2, 3, 4 },
		{ 5, 6, 7, 8 },
		{ 9, 8, 7, 6 },
		{ 5, 4, 3, 2 }
	};

	A.initFromData(data);

	Matrix B = Matrix::Make4x4();
	B.initFromData(data);

	EXPECT_TRUE(A.isEqual(B));
}

/*Scenario: Matrix equality with different matrices 
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
	Matrix A = Matrix::Make4x4();
	std::vector<std::vector<double>> data{
		{ 1, 2, 3, 4 },
		{ 5, 6, 7, 8 },
		{ 9, 8, 7, 6 },
		{ 5, 4, 3, 2 }
	};

	A.initFromData(data);

	Matrix B = Matrix::Make4x4();
	std::vector<std::vector<double>> data2{
	{ 2, 3, 4, 5 },
	{ 6, 7, 8, 9 },
	{ 8, 7, 6, 5 },
	{ 4, 3, 2, 1 }
	};

	B.initFromData(data2);

	EXPECT_FALSE(A.isEqual(B));
}