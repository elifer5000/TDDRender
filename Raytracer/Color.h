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

	Color hadamard_product(const Color& rhs) {
		Color tmp(*this);
		tmp.setR(r() * rhs.r());
		tmp.setG(g() * rhs.g());
		tmp.setB(b() * rhs.b());

		return tmp;
	}
};

//class RAYTRACER_DECLSPEC Color : public Tuple {
//public:
//	Color(double red, double green, double blue) : Tuple(red, green, blue, 0.f) {}
//
//    double& r() { return x; }
//    double& g() { return y; }
//    double& b() { return z; }
//    const double& r() const { return x; }
//    const double& g() const { return y; }
//    const double& b() const { return z; }
//};