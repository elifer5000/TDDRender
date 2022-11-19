#pragma once
#include <memory>
#include <vector>
#include "Export.h"
#include "Utils.h"


class CLASS_DECLSPEC Matrix {
public:
	Matrix(int _rows, int _cols) : rows(_rows), cols(_cols) {
		data = std::make_unique<double[]>(rows * cols);
		identity();
	}

	int nRows() { return rows; }
	int nCols() { return cols; }

	void zero() {
		fill(0);		
	}

	void fill(double val) {
		int sz = rows * cols;
		for (int i = 0; i < sz; i++) {
			data.get()[i] = val;
		}
	}

	void initFromData(const std::vector<std::vector<double>>& vec) {
		int r = 0, c = 0;
		for (auto itr = vec.begin(); itr != vec.end(); itr++, r++) {
			c = 0;
			for (auto itc = itr->begin(); itc != itr->end(); itc++, c++) {
				set(r, c, *itc);
			}
		}
	}

	double at(int row, int col) const { // row-first
		return data.get()[col + row * cols];
	}

	void set(int row, int col, double val) {
		data.get()[col + row * cols] = val;
	}

	void identity() {
		auto ptr = data.get();
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				(r == c) ? set(r, c, 1) : set(r, c, 0);
			}
		}
	}

	bool isEqual(const Matrix& other) {
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				if (!isEquald(at(r, c), other.at(r, c))) {
					return false;
				}
			}
		}

		return true;
	}

	static Matrix Make4x4() {
		return Matrix(4, 4);
	}
	
	static Matrix Make3x3() {
		return Matrix(3, 3);
	}
	
	static Matrix Make2x2() {
		return Matrix(2, 2);
	}
private:
	int rows, cols;
	std::unique_ptr<double[]> data;

};