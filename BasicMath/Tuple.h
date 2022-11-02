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
	~Tuple() {
		std::cout << "Tuple destroyed" << std::endl;
	}
	
	bool isPoint() { return w == 1.0f; }
	bool isVector() { return w == 0.0f; }

	const Tuple& operator+(const Tuple& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	const Tuple& operator-(const Tuple& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	}

	// Version with pointers
	/*static std::unique_ptr<Tuple> CreatePoint(float x, float y, float z) {
		return std::make_unique<Tuple>(x, y, z, 1.0f);
	}

	static std::unique_ptr<Tuple> CreateVector(float x, float y, float z) {
		return std::make_unique<Tuple>(x, y, z, 0.0f);
	}
	*/

	// Version with move semantics (it's implicit!)
	static Tuple CreatePoint(float x, float y, float z) {
		return Tuple(x, y, z, 1.0f);
	}

	static Tuple CreateVector(float x, float y, float z) {
		return Tuple(x, y, z, 0.0f);
	}

};