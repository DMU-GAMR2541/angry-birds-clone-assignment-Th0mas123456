#pragma once
#include "GameObject.h"
class DynamicObject : public GameObject{
public:

	DynamicObject() = default;
	virtual ~DynamicObject() = default;

	virtual int upCast() {
		return 2;
	}

};

