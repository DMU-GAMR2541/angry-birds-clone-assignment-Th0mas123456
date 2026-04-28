#pragma once
#include "DynamicObject.h"
class Bird : public DynamicObject{
public:
	Bird() = default;
	~Bird() = default;

	int upCast() override {
		return 1;
	}
};

