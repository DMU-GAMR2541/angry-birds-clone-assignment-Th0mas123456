#pragma once
#include "DynamicObject.h"
class Pig : public DynamicObject{
private:
	float pigHealth;
public:

	Pig() = default;
	Pig(std::string spritefl) : DynamicObject(spritefl) {};
	Pig(std::string spritefl, sf::IntRect spriteCut, float health) : DynamicObject(spritefl, spriteCut) { 
		pigHealth = health;
	};
	~Pig() = default;
};

