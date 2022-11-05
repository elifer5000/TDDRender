#pragma once
//#include <memory> // needed for new
#include <iostream>
#include "Export.h"

class CLASS_DECLSPEC Tuple {
public:
	float x;
	float y;
	float z;
	float w;

	Tuple(float _x = 0.f, float _y = 0.f, float _z = 0.f, float _w = 0.f) : x(_x), y(_y), z(_z), w(_w) {}
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

	Tuple operator+(const Tuple& rhs) {
		Tuple tmp(*this);
		tmp += rhs;

		return tmp;
	}

	Tuple operator-(const Tuple& rhs) {
		Tuple tmp(*this);
		tmp -= rhs;

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

	Tuple& operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;

		return *this;
	}

	Tuple& operator/=(float scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		w /= scalar;

		return *this;
	}

	// Negation overload
	Tuple operator-() {
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

	Tuple operator*(float scalar) {
		Tuple tmp(*this);
		tmp *= scalar;

		return tmp;
	}

	Tuple operator/(float scalar) {
		Tuple tmp(*this);
		tmp /= scalar;

		return tmp;
	}

	float magnitude() const {
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

	float dot(const Tuple& rhs) const {
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
	/*static std::unique_ptr<Tuple> CreatePoint(float x, float y, float z) {
		return std::make_unique<Tuple>(x, y, z, 1.0f);
	}

	static std::unique_ptr<Tuple> CreateVector(float x, float y, float z) {
		return std::make_unique<Tuple>(x, y, z, 0.0f);
	}
	*/

	// Version with move semantics (it's implicit!)
	// https://stackoverflow.com/questions/28604816/proper-use-of-std-move-for-a-factory-class
	static Tuple CreatePoint(float x, float y, float z) {
		return Tuple(x, y, z, 1.0f);
	}

	static Tuple CreateVector(float x, float y, float z) {
		return Tuple(x, y, z, 0.0f);
	}

};