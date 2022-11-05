#pragma once
#include <array>
#include <memory>
#include <iostream>
#include <fstream>
#include "Export.h"
#include "Color.h"

class CLASS_DECLSPEC Canvas {
private:
	std::unique_ptr<Color[]> pixels;
public:
	int width, height;
	Canvas(int w, int h) : width(w), height(h) {
		pixels = std::make_unique<Color[]>(w * h);
		initColor(Color());
	}

	inline int getTotalSize() const {
		return width * height;
	}

	void initColor(const Color& c) {
		int sz = getTotalSize();
		for (int i = 0; i < sz; i++) {
			pixels.get()[i] = c;
		}
	}

	void writePixel(int x, int y, Color color) {
		pixels.get()[x + width * y] = color;
	}

	Color pixelAt(int x, int y) const {
		return pixels.get()[x + width * y];
	}

	void save() {
		std::ofstream ofs;

		ofs.open(".\\image.ppm", std::ios::out);
		if (!ofs) {
			std::cout << "Unable to open file to write" << std::endl;
			return;
		}

		ofs << "P3" << std::endl;
		ofs << width << " " << height << std::endl;
		ofs << "255" << std::endl;

		ofs.close();

		int sz = getTotalSize();
		for (int i = 0; i < sz; i++) {
		}
	}
};
