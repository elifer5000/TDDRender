#include "pch.h"
#include "Light.h"
#include "Material.h"

Color RAYTRACER_DECLSPEC lighting(const Material& material, const PointLight& light,
	const Tuple& position, const Tuple& eye, const Tuple& normal) {

	// Combine the surface color with the light's color/intensity
	auto effectiveColor = material.m_color * light.getIntensity();
	
	// Find the direction to the light source
	auto lightVec = (light.getPosition() - position).normalize();
	
	// Compute the ambient contribution
	auto ambient = effectiveColor * material.m_ambient;
		
	// lightDotNormal represents the cosine of the angle between the
	// light vector and the normal vector. A negative number means the
	// light is on the other side of the surface.
	
	auto lightDotNormal = lightVec.dot(normal);
	if (lightDotNormal < 0) {
		return ambient; // No contribution from diffuse and specular
	}
	else {
		// Compute the diffuse contribution
		auto diffuse = effectiveColor * material.m_diffuse * lightDotNormal;
		// reflectDotEye represents the cosine of the angle between the
		// reflection vector and the eye vector. A negative number means the
		// light reflects away from the eye.
		auto reflectVect = Tuple::Reflect(-lightVec, normal);
		auto reflectDotEye = reflectVect.dot(eye);

		Color specular; // Default is black
		if (reflectDotEye > 0) {
			// Compute the specular contribution
			auto factor = pow(reflectDotEye, material.shininess);
			specular = light.getIntensity() * material.specular * factor;
		}
			
		//Add the three contributions together to get the final shading
		return ambient + diffuse + specular;
	}
}