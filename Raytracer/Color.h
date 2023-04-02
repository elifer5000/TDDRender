#pragma once
#include "Export.h"
#include "Tuple.h"

class RAYTRACER_DECLSPEC Color : public Tuple {
public:
	Color(double red = 0.f, double green = 0.f, double blue = 0.f) : Tuple(red, green, blue, 0.f) {
		
	}

	Color(const Tuple& other) {
		x() = other.x();
		y() = other.y();
		z() = other.z();
		w() = other.w();
	}

    double& r() { return m_x; }
    double& g() { return m_y; }
    double& b() { return m_z; }
    const double& r() const { return m_x; }
    const double& g() const { return m_y; }
    const double& b() const { return m_z; }
	void setR(double r) { m_x = r; }
	void setG(double g) { m_y = g; }
	void setB(double b) { m_z = b; }

	Color operator*(const Color& rhs) const {
		Color tmp(*this);
		tmp.setR(r() * rhs.r());
		tmp.setG(g() * rhs.g());
		tmp.setB(b() * rhs.b());

		return tmp;
	}

	Color operator*(double scalar) const {
		Color tmp(*this);
		tmp *= scalar;

		return tmp;
	}

	Color& operator*=(double scalar) {
		Tuple::operator*=(scalar);

		return *this;
	}
};