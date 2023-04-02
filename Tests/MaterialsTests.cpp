#include "pch.h"
#include "Material.h"
#include "Light.h"

/*
Scenario: The default material Given m ← material()
Then m.color = color(1, 1, 1)
And m.ambient = 0.1
And m.diffuse = 0.9
And m.specular = 0.9 And m.shininess = 200.0
*/
TEST(Material, DefaultMaterial) {
	auto m = Material();
	auto expColor = Color(1, 1, 1);
	EXPECT_TRUE(m.m_color.isEqual(expColor));
	EXPECT_EQ(m.m_ambient, 0.1);
	EXPECT_EQ(m.m_diffuse, 0.9);
	EXPECT_EQ(m.specular, 0.9);
	EXPECT_EQ(m.shininess, 200.0);
}

/*
Background:
Given m ← material()
And position ← point(0, 0, 0)
*/
class MaterialLightTests : public ::testing::Test {
protected:
	void SetUp() override {
		position = Tuple::CreatePoint();
	}

	// void TearDown() override {}

	Material material;
	Tuple position;
};

/*
Scenario: Lighting with the eye between the light and the surface
Given eyev ← vector(0, 0, -1)
And normalv ← vector(0, 0, -1)
And light ← point_light(point(0, 0, -10), color(1, 1, 1))
When result ← lighting(m, light, position, eyev, normalv)
Then result = color(1.9, 1.9, 1.9)
*/
TEST_F(MaterialLightTests, LightingEyeInMiddle) {
	auto eye = Tuple::CreateVector(0, 0, -1);
	auto normal = Tuple::CreateVector(0, 0, -1);
	auto light = PointLight(Tuple::CreatePoint(0, 0, -10), Color(1, 1, 1));

	auto result = lighting(material, light, position, eye, normal);
	auto expected = Color(1.9, 1.9, 1.9);
	EXPECT_TRUE(result.isEqual(expected));
}

/*
Scenario: Lighting with the eye between light and surface, eye offset 45°
Given eyev ← vector(0, √2/2, -√2/2)
And normalv ← vector(0, 0, -1)
And light ← point_light(point(0, 0, -10), color(1, 1, 1))
When result ← lighting(m, light, position, eyev, normalv)
Then result = color(1.0, 1.0, 1.0)
*/
TEST_F(MaterialLightTests, LightingEye45) {
	auto eye = Tuple::CreateVector(0, sqrt(2)/2, -sqrt(2)/2);
	auto normal = Tuple::CreateVector(0, 0, -1);
	auto light = PointLight(Tuple::CreatePoint(0, 0, -10), Color(1, 1, 1));

	auto result = lighting(material, light, position, eye, normal);
	auto expected = Color(1.0, 1.0, 1.0);
	EXPECT_TRUE(result.isEqual(expected));
}

/*
Scenario: Lighting with eye opposite surface, light offset 45°
Given eyev ← vector(0, 0, -1)
And normalv ← vector(0, 0, -1)
And light ← point_light(point(0, 10, -10), color(1, 1, 1))
When result ← lighting(m, light, position, eyev, normalv) 
Then result = color(0.7364, 0.7364, 0.7364)
*/
TEST_F(MaterialLightTests, LightingEyeOppositeSurface) {
	auto eye = Tuple::CreateVector(0, 0, -1);
	auto normal = Tuple::CreateVector(0, 0, -1);
	auto light = PointLight(Tuple::CreatePoint(0, 10, -10), Color(1, 1, 1));

	auto result = lighting(material, light, position, eye, normal);
	auto expected = Color(0.7364, 0.7364, 0.7364);
	EXPECT_TRUE(result.isEqual(expected));
}

/*
Scenario: Lighting with eye in the path of the reflection vector
Given eyev ← vector(0, -√2/2, -√2/2)
And normalv ← vector(0, 0, -1)
And light ← point_light(point(0, 10, -10), color(1, 1, 1)) 
When result ← lighting(m, light, position, eyev, normalv) 
Then result = color(1.6364, 1.6364, 1.6364)
*/
TEST_F(MaterialLightTests, LightingEyeInReflectionPath) {
	auto eye = Tuple::CreateVector(0, -sqrt(2)/2, -sqrt(2)/2);
	auto normal = Tuple::CreateVector(0, 0, -1);
	auto light = PointLight(Tuple::CreatePoint(0, 10, -10), Color(1, 1, 1));

	auto result = lighting(material, light, position, eye, normal);
	auto expected = Color(1.6364, 1.6364, 1.6364);
	EXPECT_TRUE(result.isEqual(expected));
}

/*
Scenario: Lighting with the light behind the surface 
Given eyev ← vector(0, 0, -1)
And normalv ← vector(0, 0, -1)
And light ← point_light(point(0, 0, 10), color(1, 1, 1))
When result ← lighting(m, light, position, eyev, normalv) 
Then result = color(0.1, 0.1, 0.1)
*/
TEST_F(MaterialLightTests, LightingLightBehindSurface) {
	auto eye = Tuple::CreateVector(0, 0, -1);
	auto normal = Tuple::CreateVector(0, 0, -1);
	auto light = PointLight(Tuple::CreatePoint(0, 0, 10), Color(1, 1, 1));

	auto result = lighting(material, light, position, eye, normal);
	auto expected = Color(0.1, 0.1, 0.1);
	EXPECT_TRUE(result.isEqual(expected));
}