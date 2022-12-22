#pragma once

// Base object class for primitives (and maybe more?)
class Object {
	inline static int s_idCounter = 0;
	int m_id;
public:
	Object() {
		m_id = s_idCounter++;
	}

	int id() {
		return m_id;
	}
};