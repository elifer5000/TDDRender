#pragma once
#include "Export.h"
#include "Tuple.h"
#include "Color.h"

class RAYTRACER_DECLSPEC PointLight {
	Color m_intensity;
	Tuple m_position;
public:
	PointLight(const Tuple& position, const Color& intensity) :
		m_position(position), m_intensity(intensity)
	{
	}

	Color getIntensity() { return m_intensity; }
	const Color& getIntensity() const { return m_intensity; }

	Tuple getPosition() { return m_position; }
	const Tuple& getPosition() const { return m_position; }

	PointLight& setPosition(const Tuple& position) { 
		m_position = position;
		return *this;
	}
	
	PointLight& setIntensity(const Color& intensity) { 
		m_intensity = intensity;
		return *this;
	}
};

class Material;
Color RAYTRACER_DECLSPEC lighting(const Material& material, const PointLight& light, const Tuple& position, const Tuple& eye, const Tuple& normal);