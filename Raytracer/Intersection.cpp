#include "pch.h"
#include <algorithm>
#include "Intersection.h"

const std::optional<Intersection> Intersections::hit() {
	// Keep array sorted 
	if (m_isDirty) {
		std::stable_sort(m_intersections.begin(), m_intersections.end(),
			[](const Intersection& arg1, const Intersection& arg2) { return arg1.m_t < arg2.m_t; }
		);
		m_isDirty = false;
	}
	// Find first non-negative number
	auto result = std::find_if(m_intersections.begin(), m_intersections.end(), [](const Intersection& arg) { return arg.m_t >= 0; });
	if (result != m_intersections.end()) {
		return { *result };
	}

	return std::nullopt;
}

void Intersections::add(const Intersection& intersection) {
	m_intersections.push_back(intersection);
	m_isDirty = true;
}

const std::optional<Intersection> Intersections::get(int at) const {
	if (at < 0 || at > (int)m_intersections.size() - 1) {
		return std::nullopt;
	}
	return { m_intersections[at] };
}

unsigned int Intersections::count() const {
	return static_cast<unsigned int>(m_intersections.size());
}

Intersection& Intersections::operator[](int index) {
	return m_intersections[index];
}