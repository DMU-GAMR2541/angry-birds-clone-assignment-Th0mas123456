#pragma once
#include "DynamicObject.h"
class Bird : public DynamicObject{
public:
	Bird() = default;
	Bird(std::string spriteLoc) : DynamicObject(spriteLoc) {};
	Bird(b2World& b2_world, b2Vec2 b2_posIn, std::string spriteLoc, sf::IntRect spriteCut) : DynamicObject(b2_world, b2_posIn, spriteLoc, spriteCut) {
	};
	~Bird() = default;
};

