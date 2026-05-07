#pragma once
#include "StaticObject.h"
class NonInteractable : public StaticObject{
public:

	NonInteractable() = default;
	NonInteractable(sf::Vector2f size, sf::Vector2f position, sf::Color color) : StaticObject(size, position, color) {};
	~NonInteractable() = default;
};

