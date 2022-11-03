#include "pch.h"
#include "Tuple.h"
#include "Utils.h"

bool Tuple::isEqual(const Tuple& rhs) {
	return isEqualf(x, rhs.x) && isEqualf(y, rhs.y) &&
		isEqualf(z, rhs.z) && isEqualf(w, rhs.w);
}