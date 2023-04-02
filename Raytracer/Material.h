#pragma once
#include "Export.h"
#include "Color.h"

class RAYTRACER_DECLSPEC Material {
public:
	Color m_color;
	double m_ambient;
	double m_diffuse;
	double specular;
	double shininess;

	Material(const Color& color = Color(1, 1, 1),
		double ambient = 0.1,
		double diffuse = 0.9,
		double specular = 0.9,
		double shininess = 200)
		: m_color(color)
		, m_ambient(ambient)
		, m_diffuse(diffuse)
		, specular(specular)
		, shininess(shininess)
	{
	}
	bool operator==(const Material& other) const {
		return m_color.isEqual(other.m_color) &&
			m_ambient == other.m_ambient &&
			m_diffuse == other.m_diffuse &&
			specular == other.specular &&
			shininess == other.shininess;
	}
};