#include "pch.h"
#include "Matrix.h"

namespace Transforms {
	Matrix4 MakeTranslation(double x, double y, double z) {
		Matrix4 m;
		m(0, 3) = x;
		m(1, 3) = y;
		m(2, 3) = z;

		return m;
	}

	Matrix4 MakeScale(double x, double y, double z) {
		Matrix4 m;
		m(0, 0) *= x;
		m(1, 1) *= y;
		m(2, 2) *= z;

		return m;
	}

	Matrix4 MakeRotateX(double rad) {
		Matrix4 m;
		m(1, 1) = m(2, 2) = cos(rad);
		m(1, 2) = -(m(2, 1) = sin(rad));

		return m;
	}

	Matrix4 MakeRotateY(double rad) {
		Matrix4 m;
		//m(1, 2) = m(2, 3) = cos(rad);
		//m(1, 3) = -(m(2, 1) = sin(rad));

		return m;
	}

	Matrix4 MakeRotateZ(double rad) {
		Matrix4 m;
		//m(1, 2) = m(2, 3) = cos(rad);
		//m(1, 3) = -(m(2, 1) = sin(rad));

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

template<> Matrix4& Matrix4::rotateX(double rad) {
	auto m = Transforms::MakeRotateX(rad);
	*this = (*this) * m;

	return *this;
}

template<> Matrix4& Matrix4::rotateY(double rad) {
	auto m = Transforms::MakeRotateY(rad);
	*this = (*this) * m;

	return *this;
}

template<> Matrix4& Matrix4::rotateZ(double rad) {
	auto m = Transforms::MakeRotateZ(rad);
	*this = (*this) * m;

	return *this;
}