#pragma once
//#include <memory> // needed for new
#include <iostream>
#include "Export.h"

class RAYTRACER_DECLSPEC Tuple {
protected:
	double m_x;
	double m_y;
	double m_z;
	double m_w;

public:
	Tuple(double _x = 0, double _y = 0, double _z = 0, double _w = 0) : m_x(_x), m_y(_y), m_z(_z), m_w(_w) {}
	Tuple(const Tuple& tuple) {
		m_x = tuple.m_x;
		m_y = tuple.m_y;
		m_z = tuple.m_z;
		m_w = tuple.m_w;
	}
	~Tuple() {
		/*std::cout << "Tuple destroyed" << std::endl;*/
	}

	auto x() -> double& { return m_x; }
	auto x() const -> const double& { return m_x; }
	auto y() -> double& { return m_y; }
	auto y() const -> const double& { return m_y; }
	auto z() -> double& { return m_z; }
	auto z() const -> const double& { return m_z; }
	auto w() -> double& { return m_w; }
	auto w() const -> const double& { return m_w; }

	bool isPoint() const { return m_w == 1.0f; }
	bool isVector() const { return m_w == 0.0f; }

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
		m_x += rhs.m_x;
		m_y += rhs.m_y;
		m_z += rhs.m_z;
		m_w += rhs.m_w;

		return *this;
	}

	Tuple& operator-=(const Tuple& rhs) {
		m_x -= rhs.m_x;
		m_y -= rhs.m_y;
		m_z -= rhs.m_z;
		m_w -= rhs.m_w;

		return *this;
	}

	Tuple& operator*=(double scalar) {
		m_x *= scalar;
		m_y *= scalar;
		m_z *= scalar;
		m_w *= scalar;

		return *this;
	}

	Tuple& operator/=(double scalar) {
		m_x /= scalar;
		m_y /= scalar;
		m_z /= scalar;
		m_w /= scalar;

		return *this;
	}

	double& operator[](int idx) {
		switch (idx) {
			case 0: return m_x;
			case 1: return m_y;
			case 2: return m_z;
			case 3: return m_w;
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
		m_x *= -1.f;
		m_y *= -1.f;
		m_z *= -1.f;
		m_w *= -1.f;

		return *this;
	}

	double magnitude() const {
		return sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
	}

	Tuple& normalize() {
		auto len = magnitude();
		
		if (len > 0) {
			m_x /= len;
			m_y /= len;
			m_z /= len;
			m_w /= len;
		}

		return *this;
	}

	double dot(const Tuple& rhs) const {
		return m_x * rhs.m_x + m_y * rhs.m_y + m_z * rhs.m_z + m_w * rhs.m_w;
	}

	Tuple cross(const Tuple& rhs) const {
		Tuple tmp = CreateVector(m_y * rhs.m_z - m_z * rhs.m_y,
			m_z * rhs.m_x - m_x * rhs.m_z,
			m_x * rhs.m_y - m_y * rhs.m_x);

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
	static Tuple CreatePoint(double x = 0, double y = 0, double z = 0) {
		return Tuple(x, y, z, 1.0);
	}

	static Tuple CreateVector(double x = 0, double y = 0, double z = 0) {
		return Tuple(x, y, z, 0.0);
	}

};