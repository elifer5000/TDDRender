#pragma once
#include "Export.h"
#include "Tuple.h"

class CLASS_DECLSPEC Color : public Tuple {
public:
	Color(float red = 0.f, float green = 0.f, float blue = 0.f) : Tuple(red, green, blue, 0.f) {
		
	}

	Color(const Tuple& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}

    float& r() { return x; }
    float& g() { return y; }
    float& b() { return z; }
    const float& r() const { return x; }
    const float& g() const { return y; }
    const float& b() const { return z; }
	void setR(float r) { x = r; }
	void setG(float g) { y = g; }
	void setB(float b) { z = b; }

	Color hadamard_product(const Color& rhs) {
		Color tmp(*this);
		tmp.setR(r() * rhs.r());
		tmp.setG(g() * rhs.g());
		tmp.setB(b() * rhs.b());

		return tmp;
	}
};

//class CLASS_DECLSPEC Color : public Tuple {
//public:
//	Color(float red, float green, float blue) : Tuple(red, green, blue, 0.f) {}
//
//    float& r() { return x; }
//    float& g() { return y; }
//    float& b() { return z; }
//    const float& r() const { return x; }
//    const float& g() const { return y; }
//    const float& b() const { return z; }
//};