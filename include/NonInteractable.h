#pragma once
#include "StaticObject.h"
class NonInteractable : public StaticObject{
public:

	NonInteractable() = default;
	NonInteractable(std::string spriteLoc, sf::IntRect spriteCut, sf::Vector2f position) : StaticObject(spriteLoc, spriteCut, position) {};
	~NonInteractable() = default;
};

