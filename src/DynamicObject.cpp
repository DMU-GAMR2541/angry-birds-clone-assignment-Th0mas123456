#include "DynamicObject.h"
#include <iostream>

DynamicObject::DynamicObject(std::string spritefl)
{
	if (!sf_texture.loadFromFile(spritefl)) {
		std::cout << "failed to load texture" << spritefl << std::endl;
	}

	sp_sprite.setTexture(sf_texture);

	sp_sprite.setOrigin(sf_texture.getSize().x / 2.0f, sf_texture.getSize().y / 2.0f);
}

DynamicObject::DynamicObject(std::string spritefl, sf::IntRect spriteCut)
{
	if (!sf_texture.loadFromFile(spritefl, spriteCut)) {
		std::cout << "failed to load texture" << spritefl << std::endl;
	}

	sp_sprite.setTexture(sf_texture);

	sp_sprite.setOrigin(sf_texture.getSize().x / 2.0f, sf_texture.getSize().y / 2.0f);
}

void DynamicObject::Render(sf::RenderWindow& window)
{
	window.draw(sp_sprite);
}

void DynamicObject::Update()
{
}
