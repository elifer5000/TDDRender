#pragma once
#include "../Export.h"
#include "../Raycaster.h"
#include "../Matrix.h"

// Base object class for primitives (and maybe more?)
class RAYTRACER_DECLSPEC Object {
	inline static int s_idCounter = 0;
	int m_id;
	Matrix4 m_transform;
public:
	Object() {
		m_id = s_idCounter++;
	}

	int id() {
		return m_id;
	}

	const Matrix4& getTransform() const;

	void setTransform(const Matrix4& m);

	virtual Intersections intersect(const Ray& ray) const;
};