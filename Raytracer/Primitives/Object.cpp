#include "pch.h"
#include "Object.h"

Intersections Object::intersect(const Ray& ray) const {
	// Default - return empty
	return Intersections();
}

const Matrix4& Object::getTransform() const {
	return m_transform;
}

Matrix4 Object::getTransform() {
	return m_transform;
}

void Object::setTransform(const Matrix4& m) {
	m_transform = m;
}

const Material& Object::getMaterial() const
{
	return m_material;
}

Material Object::getMaterial()
{
	return m_material;
}

void Object::setMaterial(const Material& m)
{
	m_material = m;
}
