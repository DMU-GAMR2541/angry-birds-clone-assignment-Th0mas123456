#pragma once
#include "StaticObject.h"
#include "DynamicObject.h"

class UI : virtual StaticObject , virtual DynamicObject{
public:
	UI() = default;
	~UI() = default;
};