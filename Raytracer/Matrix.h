#pragma once
#include <memory>
#include <vector>
#include <iomanip>
#include "Export.h"
#include "Utils.h"
#include "Tuple.h"

typedef std::vector<std::vector<double>> InitVector;

template<int ROWS, int COLS> class Matrix {
public:
	Matrix() {
		static_assert(ROWS > 0 && COLS > 0, "No zero sized matrix");
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
			m_data[i] = val;
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
		return m_data[col + row * COLS];
	}

	inline void set(int row, int col, double val) {
		m_data[col + row * COLS] = val;
	}

	inline double& operator()(int row, int col) {
		return m_data[col + row * COLS];
	}

	Matrix<ROWS, COLS>& identity() {
		for (int r = 0; r < ROWS; r++) {
			for (int c = 0; c < COLS; c++) {
				(r == c) ? set(r, c, 1) : set(r, c, 0);
			}
		}

		return *this;
	}

	bool isEqual(const Matrix<ROWS, COLS>& other) const {
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
			m_data[i] = other.m_data[i];
		}

		return *this;
	}

	Matrix<ROWS, COLS> operator*(const Matrix<ROWS, COLS>& rhs) const {
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

	Tuple operator*(const Tuple& rhs) const {
		Tuple res;
		for (int r = 0; r < ROWS; r++) {
			res[r] = at(r, 0) * rhs.x() + at(r, 1) * rhs.y() +
				at(r, 2) * rhs.z() + at(r, 3) * rhs.w();
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

	// Transform functions
	Matrix<ROWS, COLS>& translate(double x, double y, double z) {
		static_assert(ROWS == 4 && COLS == 4, "translate only in Matrix4");
	}

	Matrix<ROWS, COLS>& scale(double x, double y, double z) {
		static_assert(ROWS == 4 && COLS == 4, "scale only in Matrix4");
	}

	Matrix<ROWS, COLS>& rotateX(double rad) {
		static_assert(ROWS == 4 && COLS == 4, "rotateX only in Matrix4");
	}

	Matrix<ROWS, COLS>& rotateY(double rad) {
		static_assert(ROWS == 4 && COLS == 4, "rotateY only in Matrix4");
	}

	Matrix<ROWS, COLS>& rotateZ(double rad) {
		static_assert(ROWS == 4 && COLS == 4, "rotateZ only in Matrix4");
	}

	Matrix<ROWS, COLS>& shear(double xy, double xz, double yx, double yz, double zx, double zy) {
		static_assert(ROWS == 4 && COLS == 4, "shear only in Matrix4");
	}

	// For debugging
	const Matrix<ROWS, COLS>& print() {
		for (int r = 0; r < ROWS; r++) {
			for (int c = 0; c < COLS; c++) {
				std::cout << std::fixed << std::setprecision(5) << at(r, c) << " ";
			}
			std::cout << std::endl;
		}

		return *this;
	}
private:
	double m_data[ROWS * COLS];

};

using Matrix3 = Matrix<3, 3>;
using Matrix2 = Matrix<2, 2>;
using Matrix4 = Matrix<4, 4>;

namespace Transforms {
	Matrix4 RAYTRACER_DECLSPEC MakeTranslation(double x, double y, double z);
	Matrix4 RAYTRACER_DECLSPEC MakeScale(double x, double y, double z);
	Matrix4 RAYTRACER_DECLSPEC MakeRotateX(double rad);
	Matrix4 RAYTRACER_DECLSPEC MakeRotateY(double rad);
	Matrix4 RAYTRACER_DECLSPEC MakeRotateZ(double rad);
	Matrix4 RAYTRACER_DECLSPEC MakeShear(double xy, double xz, double yx, double yz, double zx, double zy);
}

template<> inline double Matrix2::determinant() const {
	return at(0, 0) * at(1, 1) - at(0, 1) * at(1, 0);
}

template<> inline Matrix4& Matrix4::translate(double x, double y, double z) {
	auto m = Transforms::MakeTranslation(x, y, z);
	*this = m * (*this);

	return *this;
}

template<> inline Matrix4& Matrix4::scale(double x, double y, double z) {
	auto m = Transforms::MakeScale(x, y, z);
	*this = m * (*this);

	return *this;
}

template<> inline Matrix4& Matrix4::rotateX(double rad) {
	auto m = Transforms::MakeRotateX(rad);
	*this = m * (*this);

	return *this;
}

template<> inline Matrix4& Matrix4::rotateY(double rad) {
	auto m = Transforms::MakeRotateY(rad);
	*this = (*this) * m;

	return *this;
}

template<> inline Matrix4& Matrix4::rotateZ(double rad) {
	auto m = Transforms::MakeRotateZ(rad);
	*this = (*this) * m;

	return *this;
}

template<> inline Matrix4& Matrix4::shear(double xy, double xz, double yx, double yz, double zx, double zy) {
	auto m = Transforms::MakeShear(xy, xz, yx, yz, zx, zy);
	*this = (*this) * m;

	return *this;
}