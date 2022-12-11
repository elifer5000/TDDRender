#include "pch.h"
#include <cmath>
#include "Utils.h"

short comp(double a, double b) {
	double r = a - b;

	if (r > EPSILON) {
		return 1;
	}
	else if (r < -EPSILON) {
		return -1;
	}

	return 0;
}

double rad2deg(double rad) {
	return rad * 180.0 / M_PI;
}

double deg2rad(double deg) {
	return deg * M_PI / 180.0;
}