#include "pch.h"
#include "Tuple.h"
#include "Utils.h"

bool Tuple::isEqual(const Tuple& rhs) const {
	return isEqualf(x, rhs.x) && isEqualf(y, rhs.y) &&
		isEqualf(z, rhs.z) && isEqualf(w, rhs.w);
}