#pragma once
#include "../Export.h"
#include "../Raycaster.h"
#include "../Matrix.h"
#include "../Material.h"

// Base object class for primitives (and maybe more?)
class RAYTRACER_DECLSPEC Object {
	inline static int s_idCounter = 0;
	int m_id;
protected:
	Matrix4 m_transform;
	Material m_material;
public:
	Object() {
		m_id = s_idCounter++;
	}

	int id() {
		return m_id;
	}

	const Matrix4& getTransform() const;
	Matrix4 getTransform();
	void setTransform(const Matrix4& m);

	const Material& getMaterial() const;
	Material getMaterial();
	void setMaterial(const Material& m);

	virtual Intersections intersect(const Ray& ray) const;

	virtual Tuple normalAt(const Tuple& point) const = 0;
};