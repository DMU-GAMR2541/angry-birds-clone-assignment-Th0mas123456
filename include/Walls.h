#pragma once
#include "DynamicObject.h"
#include "StaticObject.h"

class Walls : public DynamicObject{
public:
	Walls() = default;
	~Walls() = default;
	Walls(b2World& b2_world, b2Vec2 b2_posIn, sf::Vector2f size, sf::Color colour) : DynamicObject(b2_world, b2_posIn, size, colour) {};
};

