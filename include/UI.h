#pragma once
#include "StaticObject.h"
#include "DynamicObject.h"

class UI : public virtual StaticObject , public virtual DynamicObject{
public:
	UI() = default;
	~UI() = default;
};