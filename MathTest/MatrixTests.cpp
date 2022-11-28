#include "pch.h"
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

/*
Scenario: Multiplying a matrix by the identity matrix
Given the following matrix A:
|0|1| 2| 4|
|1|2| 4| 8|
|2|4| 8|16|
|4|8|16|32|
Then A * identity_matrix = A
*/

TEST(Matrices, IdentityMatrix) {
	InitVector data{
		{ 0, 1, 2, 4 },
		{ 1, 2, 4, 8 },
		{ 2, 4, 8, 16 },
		{ 4, 8, 16, 32 }
	};

	Matrix A = Matrix4(data);
	Matrix identity = Matrix4().identity(); // Default constructor is also identiy, but to be explicit

	EXPECT_TRUE((A * identity).isEqual(A));
}

/*
Scenario: Multiplying the identity matrix by a tuple
Given a ← tuple(1, 2, 3, 4)
Then identity_matrix * a = a
*/
TEST(Matrices, IdentityMatrixWithTuple) {
	auto a = Tuple(1, 2, 3, 4);

	Matrix identity = Matrix4().identity(); // Default constructor is also identiy, but to be explicit

	EXPECT_TRUE((identity * a).isEqual(a));
}

/*
Scenario: Transposing a matrix
Given the following matrix A:
|0|9|3|0|
|9|8|0|8|
|1|8|5|3| 
|0|0|5|8|
Then transpose(A) is the following matrix:
|0|9|1|0|
|9|8|8|0|
|3|0|5|5|
|0|8|3|8|
*/
TEST(Matrices, TransposeMatrix) {
	InitVector data{
		{ 0, 9, 3, 0 },
		{ 9, 8, 0, 8 },
		{ 1, 8, 5, 3 },
		{ 0, 0, 5, 8 }
	};

	auto A = Matrix4(data);

	InitVector data2{
	{ 0, 9, 1, 0 },
	{ 9, 8, 8, 0 },
	{ 3, 0, 5, 5 },
	{ 0, 8, 3, 8 }
	};

	auto expected = Matrix4(data2);

	EXPECT_TRUE(A.transpose().isEqual(expected));
}

/*
Scenario: Transposing the identity matrix
Given A ← transpose(identity_matrix)
Then A = identity_matrix
*/
TEST(Matrices, TransposeIdentityMatrix) {
	auto A = Matrix4();

	auto identity = Matrix4();

	EXPECT_TRUE(A.transpose().isEqual(identity));
}

/*
Scenario: Calculating the determinant of a 2x2 matrix
Given the following 2x2 matrix A:
| 1|5|
| -3 | 2 |
Then determinant(A) = 17
*/
TEST(Matrices, Determinant2x2) {
	InitVector data{
		{ 1, 5 },
		{ -3, 2 }
	};

	auto A = Matrix2(data);

	EXPECT_TRUE(isEquald(A.determinant(), 17));
}

/*
Scenario: A submatrix of a 3x3 matrix is a 2x2 matrix
Given the following 3x3 matrix A:
| 1|5| 0|
|-3|2| 7|
| 0|6|-3|
Then submatrix(A, 0, 2) is the following 2x2 matrix: 
| -3|2|
| 0 |6|
*/
TEST(Matrices, SubMatrix3) {
	InitVector data{
		{ 1, 5, 0 },
		{ -3, 2, 7 },
		{ 0, 6, -3}
	};

	auto A = Matrix3(data);

	InitVector data2{
		{ -3, 2 },
		{ 0, 6}
	};

	auto expected = Matrix2(data2);

	EXPECT_TRUE(A.subMatrix(0, 2).isEqual(expected));
}

/*
Scenario: A submatrix of a 4x4 matrix is a 3x3 matrix
Given the following 4x4 matrix A :
|-6| 1| 1| 6|
|-8| 5| 8| 6|
|-1| 0| 8| 2|
|-7| 1|-1| 1|
Then submatrix(A, 2, 1) is the following 3x3 matrix: 
|-6| 1|6|
|-8| 8|6|
| -7 | -1 | 1 |
*/
TEST(Matrices, SubMatrix4) {
	InitVector data{
		{ -6, 1, 1, 6 },
		{ -8, 5, 8, 6 },
		{ -1, 0, 8, 2 },
		{ -7, 1, -1, 1 }
	};

	auto A = Matrix4(data);

	InitVector data2{
		{ -6, 1, 6 },
		{ -8, 8, 6 },
		{ -7, -1, 1 }
	};

	auto expected = Matrix3(data2);

	EXPECT_TRUE(A.subMatrix(2, 1).isEqual(expected));
}

/*
Scenario: Calculating a minor of a 3x3 matrix
Given the following 3x3 matrix A:
| 3| 5| 0|
| 2|-1|-7|
| 6|-1| 5|
And B ← submatrix(A, 1, 0)
Then determinant(B) = 25
And minor(A, 1, 0) = 25
*/
TEST(Matrices, Minor3x3) {
	InitVector data{
		{ 3, 5, 0 },
		{ 2, -1, -7 },
		{ 6, -1, 5 }
	};

	auto A = Matrix3(data);

	auto B = A.subMatrix(1, 0);
	auto det = B.determinant();

	EXPECT_TRUE(isEquald(det, 25));
	EXPECT_TRUE(isEquald(A.minor(1, 0), 25));
}

/*
Scenario: Calculating a cofactor of a 3x3 matrix
Given the following 3x3 matrix A:
|3|5|0|
| 2|-1|-7|
| 6|-1| 5|
Then minor(A, 0, 0) = -12
And cofactor(A, 0, 0) = -12 
And minor(A, 1, 0) = 25
And cofactor(A, 1, 0) = -25
*/
TEST(Matrices, Cofactor3x3) {
	InitVector data{
		{ 3, 5, 0 },
		{ 2, -1, -7 },
		{ 6, -1, 5 }
	};

	auto A = Matrix3(data);

	EXPECT_TRUE(isEquald(A.minor(0, 0), -12));
	EXPECT_TRUE(isEquald(A.cofactor(0, 0), -12));
	EXPECT_TRUE(isEquald(A.minor(1, 0), 25));
	EXPECT_TRUE(isEquald(A.cofactor(1, 0), -25));
}

/*
Scenario: Calculating the determinant of a 3x3 matrix
Given the following 3x3 matrix A:
|1|2|6|
|-5| 8|-4|
|2|6|4|
Then cofactor(A, 0, 0) = 56
And cofactor(A, 0, 1) = 12
And cofactor(A, 0, 2) = -46
And determinant(A) = -196
*/
TEST(Matrices, Determinant3x3) {
	InitVector data{
		{ 1, 2, 6 },
		{ -5, 8, -4 },
		{ 2, 6, 4 }
	};

	auto A = Matrix3(data);

	EXPECT_TRUE(isEquald(A.cofactor(0, 0), 56));
	EXPECT_TRUE(isEquald(A.cofactor(0, 1), 12));
	EXPECT_TRUE(isEquald(A.cofactor(0, 2), -46));
	EXPECT_TRUE(isEquald(A.determinant(), -196));
}

/*Scenario: Calculating the determinant of a 4x4 matrix
Given the following 4x4 matrix A :
|-2|-8| 3| 5|
|-3| 1| 7| 3|
| 1| 2|-9| 6|
|-6| 7| 7|-9|
Then cofactor(A, 0, 0) = 690 
And cofactor(A, 0, 1) = 447 
And cofactor(A, 0, 2) = 210 
And cofactor(A, 0, 3) = 51
And determinant(A) = -4071
*/
TEST(Matrices, Determinant4x4) {
	InitVector data{
		{ -2, -8, 3, 5 },
		{ -3, 1, 7, 3 },
		{ 1, 2, -9, 6 },
		{ -6, 7, 7, -9 }
	};

	auto A = Matrix4(data);

	EXPECT_TRUE(isEquald(A.cofactor(0, 0), 690));
	EXPECT_TRUE(isEquald(A.cofactor(0, 1), 447));
	EXPECT_TRUE(isEquald(A.cofactor(0, 2), 210));
	EXPECT_TRUE(isEquald(A.cofactor(0, 3), 51));
	EXPECT_TRUE(isEquald(A.determinant(), -4071));
}

/*
Scenario: Testing an invertible matrix for invertibility
Given the following 4x4 matrix A:
|6|4|4|4|
|5|5|7|6|
| 4|-9| 3|-7|
| 9| 1| 7|-6|
Then determinant(A) = -2120
And A is invertible
*/
TEST(Matrices, TestInvertible1) {
	InitVector data{
		{ 6, 4, 4, 4 },
		{ 5, 5, 7, 6 },
		{ 4, -9, 3, -7 },
		{ 9, 1, 7, -6 }
	};

	auto A = Matrix4(data);

	EXPECT_TRUE(isEquald(A.determinant(), -2120));
	EXPECT_TRUE(A.isReversible());
}

/*
Scenario: Testing a noninvertible matrix for invertibility
Given the following 4x4 matrix A:
|-4| 2|-2|-3|
|9|6|2|6|
| 0|-5| 1|-5|
|0|0|0|0|
Then determinant(A) = 0 And A is not invertible
*/
TEST(Matrices, TestInvertible2) {
	InitVector data{
		{ -4, 2, -2, -3 },
		{ 9, 6, 2, 6 },
		{ 0, -5, 1, -5 },
		{ 0, 0, 0, 0 }
	};

	auto A = Matrix4(data);

	EXPECT_TRUE(isEquald(A.determinant(), 0));
	EXPECT_FALSE(A.isReversible());
}

/*
Scenario: Calculating the inverse of a matrix
Given the following 4x4 matrix A:
|-5| 2| 6|-8|
| 1|-5| 1| 8|
| 7| 7|-6|-7|
| 1|-3| 7| 4|
And B ← inverse(A)
Then determinant(A) = 532
And cofactor(A, 2, 3) = -160
And B[3,2] = -160/532
And cofactor(A, 3, 2) = 105
And B[2,3] = 105/532
And B is the following 4x4 matrix:
| 0.21805 | 0.45113 | 0.24060 | -0.04511 |
| -0.80827 | -1.45677 | -0.44361 | 0.52068 |
| -0.07895 | -0.22368 | -0.05263 | 0.19737 |
| -0.52256 | -0.81391 | -0.30075 | 0.30639 |
*/
TEST(Matrices, Inversion) {
	InitVector data{
		{ -5, 2, 6, -8 },
		{ 1, -5, 1, 8 },
		{ 7, 7, -6, -7 },
		{ 1, -3, 7, 4 }
	};

	auto A = Matrix4(data);

	auto B = A.inverse();

	EXPECT_TRUE(isEquald(A.determinant(), 532));
	EXPECT_TRUE(isEquald(A.cofactor(2, 3), -160));
	EXPECT_TRUE(isEquald(B(3, 2), -160.0/532.0));
	EXPECT_TRUE(isEquald(A.cofactor(3, 2), 105));
	EXPECT_TRUE(isEquald(B(2, 3), 105.0 / 532.0));

	InitVector data2{
		{ 0.21805 , 0.45113 , 0.24060 , -0.04511 },
		{ -0.80827 , -1.45677 , -0.44361 , 0.52068 },
		{ -0.07895 , -0.22368 , -0.05263 , 0.19737 },
		{ -0.52256 , -0.81391 , -0.30075 , 0.30639 }
	};
	auto expected = Matrix4(data2);

	EXPECT_TRUE(B.isEqual(expected));
}

/*
Scenario: Calculating the inverse of another matrix
Given the following 4x4 matrix A:
| 8|-5| 9| 2|
|7|5|6|1|
|-6| 0| 9| 6|
|-3| 0|-9|-4|
Then inverse(A) is the following 4x4 matrix:
| -0.15385 | -0.15385 | -0.28205 | -0.53846 |
| -0.07692 | 0.12308 | 0.02564 | 0.03077 |
| 0.35897 | 0.35897 | 0.43590 | 0.92308 |
| -0.69231 | -0.69231 | -0.76923 | -1.92308 |
*/
TEST(Matrices, Inversion2) {
	InitVector data{
		{ 8, -5, 9, 2 },
		{ 7, 5, 6, 1 },
		{ -6, 0, 9, 6 },
		{ -3, 0, -9, -4 }
	};

	auto A = Matrix4(data);

	auto B = A.inverse();

	InitVector data2{
		{ -0.15385, -0.15385, -0.28205, -0.53846 },
		{ -0.07692, 0.12308, 0.02564, 0.03077 },
		{ 0.35897, 0.35897, 0.43590, 0.92308 },
		{ -0.69231, -0.69231, -0.76923, -1.92308 }
	};
	auto expected = Matrix4(data2);

	EXPECT_TRUE(B.isEqual(expected));
}

/*Scenario: Calculating the inverse of a third matrix
Given the following 4x4 matrix A:
|9|3|0|9|
| -5 | -2 | -6 | -3 |
|-4| 9| 6| 4|
|-7| 6| 6| 2|
Then inverse(A) is the following 4x4 matrix:
| -0.04074 | -0.07778 | 0.14444 | -0.22222 |
| -0.07778 | 0.03333 | 0.36667 | -0.33333 |
| -0.02901 | -0.14630 | -0.10926 | 0.12963 | 
| 0.17778 | 0.06667 | -0.26667 | 0.33333 |
*/

TEST(Matrices, Inversion3) {
	InitVector data{
		{ 9, 3, 0, 9 },
		{ -5, -2, -6, -3},
		{ -4, 9, 6, 4 },
		{ -7, 6, 6, 2 }
	};

	auto A = Matrix4(data);

	auto B = A.inverse();

	InitVector data2{
		{ -0.04074, -0.07778, 0.14444, -0.22222 },
		{ -0.07778, 0.03333, 0.36667, -0.33333 },
		{ -0.02901, -0.14630, -0.10926, 0.12963 },
		{ 0.17778, 0.06667, -0.26667, 0.33333 }
	};
	auto expected = Matrix4(data2);

	EXPECT_TRUE(B.isEqual(expected));
}

/*
Scenario: Multiplying a product by its inverse
Given the following 4x4 matrix A:
| 3|-9| 7| 3|
| 3|-8| 2|-9|
|-4| 4| 4| 1|
|-6| 5|-1| 1|
And the following 4x4 matrix B:
|8|2|2|2|
| 3|-1| 7| 0|
|7|0|5|4|
| 6|-2| 0| 5|
And C ← A * B
Then C * inverse(B) = A
*/
TEST(Matrices, MultiplyByInverse) {
	InitVector data{
		{  3, -9, 7, 3 },
		{  3, -8, 2, -9 },
		{ -4, 4, 4, 1 },
		{ -6, 5, -1, 1  }
	};

	InitVector data2{
		{  8, 2, 2, 2 },
		{  3, -1, 7, 0 },
		{ 7, 0, 5, 4 },
		{ 6, -2, 0, 5  }
	};

	auto A = Matrix4(data);
	auto B = Matrix4(data2);

	auto C = A * B;

	EXPECT_TRUE((C * B.inverse()).isEqual(A));

	auto D = A;
	EXPECT_TRUE(A.transpose().inverse().isEqual(D.inverse().transpose()));

}