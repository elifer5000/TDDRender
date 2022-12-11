#include "pch.h"
#include "Matrix.h"

namespace Transforms {
	Matrix4 BASICMATH_DECLSPEC MakeTranslation(double x, double y, double z) {
		Matrix4 m;
		m(0, 3) = x;
		m(1, 3) = y;
		m(2, 3) = z;

		return m;
	}

	Matrix4 BASICMATH_DECLSPEC MakeScale(double x, double y, double z) {
		Matrix4 m;
		m(0, 0) *= x;
		m(1, 1) *= y;
		m(2, 2) *= z;

		return m;
	}
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