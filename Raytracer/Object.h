#pragma once

// Base object class for primitives (and maybe more?)
class Object {
	inline static int _idCounter = 0;
	int _id;
public:
	Object() {
		_id = _idCounter++;
	}
};