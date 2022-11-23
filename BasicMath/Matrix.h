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

	void zero() {
		fill(0);		
	}

	void fill(double val) {
		int sz = ROWS * COLS;
		for (int i = 0; i < sz; i++) {
			data[i] = val;
		}
	}

	void initFromData(const InitVector& vec) {
		int r = 0, c = 0;
		for (auto itr = vec.begin(); itr != vec.end(); itr++, r++) {
			c = 0;
			for (auto itc = itr->begin(); itc != itr->end(); itc++, c++) {
				set(r, c, *itc);
			}
		}
	}

	inline double at(int row, int col) const { // row-first
		return data[col + row * COLS];
	}

	inline void set(int row, int col, double val) {
		data[col + row * COLS] = val;
	}

	void identity() {
		for (int r = 0; r < ROWS; r++) {
			for (int c = 0; c < COLS; c++) {
				(r == c) ? set(r, c, 1) : set(r, c, 0);
			}
		}
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

private:
	double data[ROWS * COLS];

};

#define Matrix3 Matrix<3, 3>
#define Matrix2 Matrix<2, 2>
#define Matrix4 Matrix<4, 4>