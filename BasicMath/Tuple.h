#pragma once
//#include <memory> // needed for new
#include <iostream>
#include "Export.h"

class BASICMATH_DECLSPEC Tuple {
public:
	double x;
	double y;
	double z;
	double w;

	Tuple(double _x = 0.f, double _y = 0.f, double _z = 0.f, double _w = 0.f) : x(_x), y(_y), z(_z), w(_w) {}
	Tuple(const Tuple& tuple) {
		x = tuple.x;
		y = tuple.y;
		z = tuple.z;
		w = tuple.w;
	}
	~Tuple() {
		/*std::cout << "Tuple destroyed" << std::endl;*/
	}
	
	bool isPoint() const { return w == 1.0f; }
	bool isVector() const { return w == 0.0f; }

	Tuple operator+(const Tuple& rhs) const {
		Tuple tmp(*this);
		tmp += rhs;

		return tmp;
	}

	Tuple operator-(const Tuple& rhs) const {
		Tuple tmp(*this);
		tmp -= rhs;

		return tmp;
	}

	Tuple operator*(double scalar) const {
		Tuple tmp(*this);
		tmp *= scalar;

		return tmp;
	}

	Tuple operator/(double scalar) const {
		Tuple tmp(*this);
		tmp /= scalar;

		return tmp;
	}

	Tuple& operator+=(const Tuple& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;

		return *this;
	}

	Tuple& operator-=(const Tuple& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;

		return *this;
	}

	Tuple& operator*=(double scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;

		return *this;
	}

	Tuple& operator/=(double scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		w /= scalar;

		return *this;
	}

	double& operator[](int idx) {
		switch (idx) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
			case 3: return w;
			default: throw "Invalid tuple index";
		}
	}

	// Negation overload
	Tuple operator-() const {
		Tuple tmp(*this);
		tmp.negate();

		return tmp;
	}

	// Self negation
	Tuple& negate() {
		x *= -1.f;
		y *= -1.f;
		z *= -1.f;
		w *= -1.f;

		return *this;
	}

	double magnitude() const {
		return sqrt(x * x + y * y + z * z + w * w);
	}

	Tuple& normalize() {
		auto len = magnitude();
		
		if (len > 0) {
			x /= len;
			y /= len;
			z /= len;
			w /= len;
		}

		return *this;
	}

	double dot(const Tuple& rhs) const {
		return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
	}

	Tuple cross(const Tuple& rhs) const {
		Tuple tmp = CreateVector(y * rhs.z - z * rhs.y,
			z * rhs.x - x * rhs.z,
			x * rhs.y - y * rhs.x);

		return tmp;
	}

	bool isEqual(const Tuple& rhs) const;

	// Version with pointers
	/*static std::unique_ptr<Tuple> CreatePoint(double x, double y, double z) {
		return std::make_unique<Tuple>(x, y, z, 1.0f);
	}

	static std::unique_ptr<Tuple> CreateVector(double x, double y, double z) {
		return std::make_unique<Tuple>(x, y, z, 0.0f);
	}
	*/

	// Version with move semantics (it's implicit!)
	// https://stackoverflow.com/questions/28604816/proper-use-of-std-move-for-a-factory-class
	static Tuple CreatePoint(double x, double y, double z) {
		return Tuple(x, y, z, 1.0f);
	}

	static Tuple CreateVector(double x, double y, double z) {
		return Tuple(x, y, z, 0.0f);
	}

};