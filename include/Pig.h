#pragma once
#include "DynamicObject.h"
class Pig : public DynamicObject{
private:
	float pigHealth;
public:

	Pig() = default;
	Pig(std::string spriteLoc) : DynamicObject(spriteLoc) {};
	Pig(std::string spriteLoc, sf::IntRect spriteCut, float health) : DynamicObject(spriteLoc, spriteCut) { 
		pigHealth = health;
	};
	~Pig() = default;
};

