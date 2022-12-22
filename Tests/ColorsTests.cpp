#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Utils.h"
#include "Color.h"
#include "Canvas.h"

/*
Scenario: Colors are (red, green, blue) tuples
Given c ← color(-0.5, 0.4, 1.7)
Then c.red = -0.5
And c.green = 0.4
And c.blue = 1.7*/
TEST(Colors, Creation) {
	Color c(-0.5f, 0.4f, 1.7f);
	EXPECT_EQ(c.r(), -0.5f);
	EXPECT_EQ(c.g(), 0.4f);
	EXPECT_EQ(c.b(), 1.7f);
}

/*
Scenario: Adding colors
Given c1 ← color(0.9, 0.6, 0.75)
And c2 ← color(0.7, 0.1, 0.25)
Then c1 + c2 = color(1.6, 0.7, 1.0)
*/
TEST(Colors, AddingColors) {
	Color c1(0.9f, 0.6f, 0.75f);
	Color c2(0.7f, 0.1f, 0.25f);
	Color res = c1 + c2;
	
	Color expected(1.6f, 0.7f, 1.0f);
	EXPECT_TRUE(res.isEqual(expected));
}


/*
Scenario: Subtracting colors
Given c1 ← color(0.9, 0.6, 0.75)
And c2 ← color(0.7, 0.1, 0.25)
Then c1 - c2 = color(0.2, 0.5, 0.5)
*/
TEST(Colors, SubstractingColors) {
	Color c1(0.9f, 0.6f, 0.75f);
	Color c2(0.7f, 0.1f, 0.25f);
	Color res = c1 - c2;

	Color expected(0.2f, 0.5f, 0.5f);
	EXPECT_TRUE(res.isEqual(expected));
}

/*
Scenario: Multiplying a color by a scalar
Given c ← color(0.2, 0.3, 0.4)
Then c * 2 = color(0.4, 0.6, 0.8)
*/
TEST(Colors, ScalarColor) {
	Color c(0.2f, 0.3f, 0.4f);
	
	Color expected(0.4f, 0.6f, 0.8f);
	EXPECT_TRUE((c * 2.f).isEqual(expected));
}

/*
Scenario: Multiplying colors
Given c1 ← color(1, 0.2, 0.4)
And c2 ← color(0.9, 1, 0.1)
Then c1 * c2 = color(0.9, 0.2, 0.04)
*/
TEST(Colors, MultiplyColors) {
	Color c1(1.0f, 0.2f, 0.4f);
	Color c2(0.9f, 1.f, 0.1f);

	Color res = c1.hadamard_product(c2);
	Color expected(0.9f, 0.2f, 0.04f);
	EXPECT_TRUE(res.isEqual(expected));
}

/*
Scenario: Creating a canvas
Given c ← canvas(10, 20)
Then c.width = 10
And c.height = 20
And every pixel of c is color(0, 0, 0)
*/
TEST(Canvas, Creation) {
	Canvas c(10, 20);

	EXPECT_EQ(c.m_width, 10);
	EXPECT_EQ(c.m_height, 20);

	Color expected(0.f, 0.f, 0.f);
	for (int x = 0; x < c.m_width; x++) {
		for (int y = 0; y < c.m_height; y++) {
			EXPECT_TRUE(c.pixelAt(x, y).isEqual(expected));
		}
	}
}

/*
Scenario: Writing pixels to a canvas
Given c ← canvas(10, 20)
And red ← color(1, 0, 0)
When write_pixel(c, 2, 3, red)
Then pixel_at(c, 2, 3) = red
*/
TEST(Canvas, WritePixel) {
	Canvas c(10, 20);

	Color red(1.f, 0.f, 0.f);
	c.writePixel(2, 3, red);
	EXPECT_TRUE(c.pixelAt(2, 3).isEqual(red));
}

/*
Scenario: Constructing the PPM header
Given c ← canvas(5, 3)
When ppm ← canvas_to_ppm(c)
Then lines 1-3 of ppm are
"""
P3
5 3
255
"""
*/
TEST(Canvas, PPMHeader) {
	Canvas c(5, 3);

	c.saveToPPM("headerTest");

	std::ifstream ifs;
	ifs.open(".\\headerTest.ppm", std::ios::in);
	
	EXPECT_TRUE(ifs); // Check can open the file
	if (!ifs) {
		return;
	}

	std::string expected[] = {
		"P3", "5 3", "255"
	};
	std::string str;
	int i = 0;
	while (!ifs.eof() && i < 3) { // i check because it's only testing the header
		std::getline(ifs, str);
		EXPECT_EQ(str, expected[i++]);
	}

	ifs.close();
}


/*
Scenario: Constructing the PPM pixel data
Given c ← canvas(5, 3)
And c1 ← color(1.5, 0, 0)
And c2 ← color(0, 0.5, 0)
And c3 ← color(-0.5, 0, 1)
When write_pixel(c, 0, 0, c1)
And write_pixel(c, 2, 1, c2)
And write_pixel(c, 4, 2, c3)
And ppm ← canvas_to_ppm(c)
Then lines 4-6 of ppm are
"""
255 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 128 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 255
"""
*/
TEST(Canvas, PPMPixelData) {
	Canvas c(5, 3);
	Color c1(1.5f, 0.f, 0.f);
	Color c2(0.f, 0.5f, 0.f);
	Color c3(-0.5f, 0.f, 1.f);

	c.writePixel(0, 0, c1);
	c.writePixel(2, 1, c2);
	c.writePixel(4, 2, c3);

	c.saveToPPM("pixelTest");

	std::ifstream ifs;
	ifs.open(".\\pixelTest.ppm", std::ios::in);

	EXPECT_TRUE(ifs); // Check can open the file
	if (!ifs) {
		return;
	}

	std::vector<std::string> expected = {
		"255 0 0 0 0 0 0 0 0 0 0 0 0 0 0",
		"0 0 0 0 0 0 0 128 0 0 0 0 0 0 0",
		"0 0 0 0 0 0 0 0 0 0 0 0 0 0 255"
	};
	std::string str;
	int i = 0;
	while (!ifs.eof() && i++ < 3) { // Skip header
		std::getline(ifs, str);
	}
	EXPECT_FALSE(ifs.eof());

	// Read lines 4-6
	i = 0;
	while (!ifs.eof() && i < expected.size()) { // i check because it's only testing the header
		std::getline(ifs, str);
		EXPECT_EQ(str, expected[i++]);
	}

	ifs.close();
}

/*
Scenario: Splitting long lines in PPM files
Given c ← canvas(10, 2)
When every pixel of c is set to color(1, 0.8, 0.6)
And ppm ← canvas_to_ppm(c)
Then lines 4-7 of ppm are
"""
255 204 153 255 204 153 255 204 153 255 204 153 255 204 153
255 204 153 255 204 153 255 204 153 255 204 153 255 204 153
255 204 153 255 204 153 255 204 153 255 204 153 255 204 153
255 204 153 255 204 153 255 204 153 255 204 153 255 204 153
"""
*/
TEST(Canvas, PPMPixelDataLongLines) {
	Canvas c(10, 2);
	Color color(1.f, 0.8f, 0.6f);
	c.fill(color);

	c.saveToPPM("pixelTestLongLines");

	std::ifstream ifs;
	ifs.open(".\\pixelTestLongLines.ppm", std::ios::in);

	EXPECT_TRUE(ifs); // Check can open the file
	if (!ifs) {
		return;
	}

	std::vector<std::string> expected = {
		"255 204 153 255 204 153 255 204 153 255 204 153 255 204 153",
		"255 204 153 255 204 153 255 204 153 255 204 153 255 204 153",
		"255 204 153 255 204 153 255 204 153 255 204 153 255 204 153",
		"255 204 153 255 204 153 255 204 153 255 204 153 255 204 153",
	};

	std::string str;
	int i = 0;
	while (!ifs.eof() && i++ < 3) { // Skip header
		std::getline(ifs, str);
	}
	EXPECT_FALSE(ifs.eof());

	// Read lines 4-6
	i = 0;
	while (!ifs.eof() && i < expected.size()) { // i check because it's only testing the header
		std::getline(ifs, str);
		EXPECT_EQ(str, expected[i++]);
	}

	ifs.close();
}


/*
Scenario: PPM files are terminated by a newline character Given c ← canvas(5, 3)
When ppm ← canvas_to_ppm(c)
Then ppm ends with a newline character
*/
TEST(Canvas, PPMEndNewline) {
	Canvas c(3, 2);
	c.saveToPPM("pixelTestNewLine");

	std::ifstream ifs;
	ifs.open(".\\pixelTestNewLine.ppm", std::ios::in);

	EXPECT_TRUE(ifs); // Check can open the file
	if (!ifs) {
		return;
	}

	std::string str;
	while (!ifs.eof()) { // i check because it's only testing the header
		std::getline(ifs, str);
		if (ifs.eof()) {
			EXPECT_EQ(str, ""); // Should contain empty line at the end
		}		
	}

	ifs.close();
}