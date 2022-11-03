#pragma once
#include <memory>
#include <iostream>

#ifdef BASICMATH_EXPORTS
#define CLASS_DECLSPEC    __declspec(dllexport)
#else
#define CLASS_DECLSPEC    __declspec(dllimport)
#endif

class CLASS_DECLSPEC Tuple {
public:
	float x;
	float y;
	float z;
	float w;

	Tuple(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
	Tuple(const Tuple& tuple) {
		x = tuple.x;
		y = tuple.y;
		z = tuple.z;
		w = tuple.w;
	}
	~Tuple() {
		/*std::cout << "Tuple destroyed" << std::endl;*/
	}
	
	bool isPoint() { return w == 1.0f; }
	bool isVector() { return w == 0.0f; }

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

	// Negation overload
	//Tuple& operator-() {
	//	Tuple tmp(*this);
	//	tmp.negate();

	//	return tmp;
	//}

	// Self negation
	Tuple& negate() {
		x *= -1.f;
		y *= -1.f;
		z *= -1.f;
		w *= -1.f;

		return *this;
	}

	bool isEqual(const Tuple& rhs);

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