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
		m(0, 0) = m(2, 2) = cos(rad);
		m(2, 0) = -(m(0, 2) = sin(rad));

		return m;
	}

	Matrix4 MakeRotateZ(double rad) {
		Matrix4 m;
		m(0, 0) = m(1, 1) = cos(rad);
		m(0, 1) = -(m(1, 0) = sin(rad));

		return m;
	}

	Matrix4 MakeShear(double xy, double xz, double yx, double yz, double zx, double zy) {
		Matrix4 m;
		m(0, 1) = xy;
		m(0, 2) = xz;
		m(1, 0) = yx;
		m(1, 2) = yz;
		m(2, 0) = zx;
		m(2, 1) = zy;
		
		return m;
	}
}