#pragma once
#include <array>
#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Export.h"
#include "Color.h"

#define MAX_COLOR_VAL 255
#define MAX_LINE_LEN 70

inline int getClampedValue(double val) {
	return std::min<int>(std::max<int>(std::lround(val * MAX_COLOR_VAL), 0), MAX_COLOR_VAL);
}

class RAYTRACER_DECLSPEC Canvas {
public:
	int width, height;
	Canvas(int w, int h) : width(w), height(h) {
		pixels = std::make_unique<Color[]>(getTotalSize());
		fill(Color());
	}

	inline int getTotalSize() const {
		return width * height;
	}

	void fill(const Color& c) {
		int sz = getTotalSize();
		for (int i = 0; i < sz; i++) {
			pixels.get()[i] = c;
		}
	}

	void writePixel(int x, int y, Color color) {
		int pos = x + width * y;
		if (pos < 0 || pos > getTotalSize() - 1) {
			return;
		}
		pixels.get()[pos] = color;
	}

	Color pixelAt(int x, int y) const {
		return pixels.get()[x + width * y];
	}

	//TODO pass an optional folder (for saving tests separately)
	//https://stackoverflow.com/questions/71658440/c17-create-directories-automatically-given-a-file-path
	void saveToPPM(std::string fileName = "image") {
		std::ofstream ofs;

		ofs.open(".\\" + fileName + ".ppm", std::ios::out);
		if (!ofs) {
			std::cout << "Unable to open file to write" << std::endl;
			return;
		}

		ofs << "P3" << std::endl;
		ofs << width << " " << height << std::endl;
		ofs << MAX_COLOR_VAL << std::endl;

		int sz = getTotalSize();
		std::string line;
		std::string space = " ";
		char colorStr[MAX_LINE_LEN];

		for (int i = 0; i < sz; i++) {
			Color& c = pixels.get()[i];
			int r = getClampedValue(c.r());
			int g = getClampedValue(c.g());
			int b = getClampedValue(c.b());
			snprintf(colorStr, MAX_LINE_LEN, "%d %d %d", r, g, b);
			size_t len = strlen(colorStr);
			if (line.size() + len + 1 > MAX_LINE_LEN ||   // Add 1 because for sure it will also have a space before
				(i > 0 && i % width == 0)) { // If it's the first in a new row
				// Flush line
				ofs << line << std::endl;
				line.clear();
			}
			
			if (line.size() > 0) {
				line += space;
			}
			
			line += colorStr;
		}

		// Flush last line
		if (line.size() > 0) {
			ofs << line << std::endl;
		}

		ofs.close();
	}
private:
	std::unique_ptr<Color[]> pixels;
};
