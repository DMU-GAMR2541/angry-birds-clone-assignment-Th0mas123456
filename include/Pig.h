#pragma once
#include "DynamicObject.h"
class Pig : public DynamicObject{
private:
	float pigHealth;
public:

	Pig() = default;
	Pig(std::string spriteLoc) : DynamicObject(spriteLoc) {};
	Pig(b2World& b2_world, b2Vec2 b2_posIn, std::string spriteLoc, sf::IntRect spriteCut, float health) : DynamicObject(b2_world, b2_posIn, spriteLoc, spriteCut) {
		pigHealth = health;
	};
	~Pig() = default;
};

