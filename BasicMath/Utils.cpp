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