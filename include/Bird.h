#pragma once
#include "DynamicObject.h"
class Bird : public DynamicObject{
public:
	Bird() = default;
	Bird(std::string spriteLoc) : DynamicObject(spriteLoc) {};
	Bird(std::string spriteLoc, sf::IntRect spriteCut, std::string birdType) : DynamicObject(spriteLoc, spriteCut) {
	};
	~Bird() = default;
};

