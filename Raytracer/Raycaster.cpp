#include "pch.h"
#include "Raycaster.h"
#include "Primitives/Object.h"

IntersectResult Ray::intersect(const Object& obj) const {
	return obj.intersect(*this);
}