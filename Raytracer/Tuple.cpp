#include "pch.h"
#include "Tuple.h"
#include "Utils.h"

bool Tuple::isEqual(const Tuple& rhs) const {
	return isEquald(x, rhs.x) && isEquald(y, rhs.y) &&
		isEquald(z, rhs.z) && isEquald(w, rhs.w);
}