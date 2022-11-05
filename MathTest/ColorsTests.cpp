#include "pch.h"
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

	EXPECT_EQ(c.width, 10);
	EXPECT_EQ(c.height, 20);

	Color expected(0.f, 0.f, 0.f);
	for (int x = 0; x < c.width; x++) {
		for (int y = 0; y < c.height; y++) {
			EXPECT_TRUE(c.pixelAt(x, y).isEqual(expected));
		}
	}

	//c.save();
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