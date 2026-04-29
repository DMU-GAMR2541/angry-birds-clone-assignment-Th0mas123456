#pragma once
#include <SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include "box2d/box2d.h"

class GameObject{
public:

	GameObject() = default;
	virtual ~GameObject() = default;
	virtual void Render(sf::RenderWindow& window) = 0;
	virtual void Update() = 0;
};

