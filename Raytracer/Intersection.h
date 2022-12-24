#pragma once
#include <vector>
#include <optional>
#include "Export.h"

class Object;

class RAYTRACER_DECLSPEC Intersection {
public:
	double m_t;
	const Object* m_object;

	//Intersection(double t, const Object& object) : m_t(t), m_object(&object) {}
	//Intersection(const Intersection& other) {
	//	*this = other;
	//}
	//Intersection& operator=(const Intersection& rhs) {
	//	m_t = rhs.m_t;
	//	m_object = rhs.m_object;

	//	return *this;
	//}
	bool operator==(const Intersection& rhs) const {
		return m_t == rhs.m_t && m_object == rhs.m_object;
	}
};

using IntersecVec = std::vector<Intersection>;

class RAYTRACER_DECLSPEC Intersections {
	IntersecVec m_intersections;
	bool m_isDirty;

public:
	Intersections() : m_isDirty(true) {}
	Intersections(const IntersecVec&& intersections) {
		m_intersections = intersections;
		m_isDirty = true;
	}

	const std::optional<Intersection> hit();
	void add(const Intersection& intersection);
	
	const std::optional<Intersection> get(int at) const;

	unsigned int count() const;

	Intersection& operator[](int index);
};