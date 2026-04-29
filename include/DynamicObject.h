#pragma once
#include "GameObject.h"
class DynamicObject : public GameObject{
private:
	sf::Sprite sp_sprite;
	sf::Texture sf_texture;
public:

	DynamicObject() = default;
	DynamicObject(std::string spritefl);
	DynamicObject(std::string spritefl, sf::IntRect spriteCut);
	virtual ~DynamicObject() = default;
	void Render(sf::RenderWindow& window);
	void Update();
};

