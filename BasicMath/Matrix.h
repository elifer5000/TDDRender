#pragma once
#include <memory>
#include <vector>
#include "Export.h"
#include "Utils.h"
#include "Tuple.h"

typedef std::vector<std::vector<double>> InitVector;

template<int ROWS, int COLS> class Matrix {
public:
	Matrix() {
		identity();
	}

	Matrix(const InitVector& vec) {
		initFromData(vec);
	}

	Matrix(const Matrix<ROWS, COLS>& other) {
		*this = other;
	}

	int nRows() { return ROWS; }
	int nCols() { return COLS; }

	Matrix<ROWS, COLS>& zero() {
		return fill(0);
	}

	Matrix<ROWS, COLS>& fill(double val) {
		int sz = ROWS * COLS;
		for (int i = 0; i < sz; i++) {
			data[i] = val;
		}

		return *this;
	}

	Matrix<ROWS, COLS>& initFromData(const InitVector& vec) {
		int r = 0, c = 0;
		for (auto itr = vec.begin(); itr != vec.end(); itr++, r++) {
			c = 0;
			for (auto itc = itr->begin(); itc != itr->end(); itc++, c++) {
				set(r, c, *itc);
			}
		}

		return *this;
	}

	inline double at(int row, int col) const { // row-first
		return data[col + row * COLS];
	}

	inline void set(int row, int col, double val) {
		data[col + row * COLS] = val;
	}

	inline double& operator()(int row, int col) {
		return data[col + row * COLS];
	}

	Matrix<ROWS, COLS>& identity() {
		for (int r = 0; r < ROWS; r++) {
			for (int c = 0; c < COLS; c++) {
				(r == c) ? set(r, c, 1) : set(r, c, 0);
			}
		}

		return *this;
	}

	bool isEqual(const Matrix<ROWS, COLS>& other) {
		for (int r = 0; r < ROWS; r++) {
			for (int c = 0; c < COLS; c++) {
				if (!isEquald(at(r, c), other.at(r, c))) {
					return false;
				}
			}
		}

		return true;
	}

	Matrix<ROWS, COLS>& operator=(const Matrix<ROWS, COLS>& other) {
		int sz = ROWS * COLS;
		for (int i = 0; i < sz; i++) {
			data[i] = other.data[i];
		}

		return *this;
	}

	Matrix<ROWS, COLS> operator*(const Matrix<ROWS, COLS>& rhs) {
		Matrix<ROWS, COLS> res;

		for (int r = 0; r < ROWS; r++) {
			for (int c = 0; c < COLS; c++) {
				res.set(r, c,
					at(r, 0) * rhs.at(0, c) +
					at(r, 1) * rhs.at(1, c) +
					at(r, 2) * rhs.at(2, c) +
					at(r, 3) * rhs.at(3, c)
				);
			}
		}

		return res;
	}

	Tuple operator*(const Tuple& rhs) {
		Tuple res;
		for (int r = 0; r < ROWS; r++) {
			res[r] = at(r, 0) * rhs.x + at(r, 1) * rhs.y +
				at(r, 2) * rhs.z + at(r, 3) * rhs.w;
		}

		return res;
	}

	Matrix<ROWS, COLS>& transpose() {
		// Swap the upper triangle matrix with lower triangle matrix
		// Diagonal stays the same
		for (int r = 0; r < ROWS; r++) {
			for (int c = r + 1; c < COLS; c++) {
				std::swap((*this)(r, c), (*this)(c, r));
			}
		}

		return *this;
	}

	double determinant() const {
		double det = 0;

		for (int c = 0; c < COLS; c++) {
			det += at(0, c) * cofactor(0, c);
		}

		return det;
	}

	double isReversible() const {
		return !isEquald(determinant(), 0);
	}

	Matrix<ROWS - 1, COLS - 1> subMatrix(int row, int col) const {
		Matrix<ROWS - 1, COLS - 1> res;

		for (int src_r = 0, dst_r = 0; dst_r < ROWS - 1; src_r++, dst_r++) {
			if (src_r == row) src_r++; // Skip this row in source

			for (int src_c = 0, dst_c = 0; dst_c < COLS - 1; src_c++, dst_c++) {
				if (src_c == col) src_c++; // Skip this column in source

				res(dst_r, dst_c) = at(src_r, src_c);
			}
		}

		return res;
	}

	double minor(int row, int col) const {
		auto sub = subMatrix(row, col);
		
		return sub.determinant();
	}

	double cofactor(int row, int col) const {
		double _minor = minor(row, col);
		if ((row + col) % 2 == 1) {
			_minor = -_minor;
		}

		return _minor;
	}

	Matrix<ROWS, COLS> inverse() {
		double det = determinant();
		if (isEquald(det, 0)) {
			// Another option: return empty matrix
			throw "Matrix not invertible";
		}

		Matrix<ROWS, COLS> res;
		for (int r = 0; r < ROWS; r++) {
			for (int c = 0; c < COLS; c++) {
				double cofac = cofactor(r, c);

				res(c, r) = cofac / det;
			}
		}

		return res;
	}

	Matrix<ROWS, COLS>& translate(double x, double y, double z) {
		static_assert(ROWS == 4 && COLS == 4, "translate only in Matrix4");
	}

	Matrix<ROWS, COLS>& scale(double x, double y, double z) {
		static_assert(ROWS == 4 && COLS == 4, "scale only in Matrix4");
	}

private:
	double data[ROWS * COLS];

};

using Matrix3 = Matrix<3, 3>;
using Matrix2 = Matrix<2, 2>;
using Matrix4 = Matrix<4, 4>;

template<> double Matrix2::determinant() const {
	return at(0, 0) * at(1, 1) - at(0, 1) * at(1, 0);
}

namespace Transforms {
	Matrix4 BASICMATH_DECLSPEC MakeTranslation(double x, double y, double z);
	Matrix4 BASICMATH_DECLSPEC MakeScale(double x, double y, double z);
}

template<> Matrix4& Matrix4::translate(double x, double y, double z) {
	auto m = Transforms::MakeTranslation(x, y, z);
	*this = (*this) * m;

	return *this;
}

template<> Matrix4& Matrix4::scale(double x, double y, double z) {
	auto m = Transforms::MakeScale(x, y, z);
	*this = (*this) * m;

	return *this;
}