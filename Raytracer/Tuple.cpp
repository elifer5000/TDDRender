#include "pch.h"
#include "Tuple.h"
#include "Utils.h"

bool Tuple::isEqual(const Tuple& rhs) const {
	return isEquald(m_x, rhs.m_x) && isEquald(m_y, rhs.m_y) &&
		isEquald(m_z, rhs.m_z) && isEquald(m_w, rhs.m_w);
}