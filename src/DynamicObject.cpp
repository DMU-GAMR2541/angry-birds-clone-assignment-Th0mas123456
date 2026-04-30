#include "DynamicObject.h"
#include <iostream>

DynamicObject::DynamicObject(std::string spriteLoc)
{
	if (!sf_texture.loadFromFile(spriteLoc)) {
		std::cout << "failed to load texture" << spriteLoc << std::endl;
	}

	sp_sprite.setTexture(sf_texture);

	sp_sprite.setOrigin(sf_texture.getSize().x / 2.0f, sf_texture.getSize().y / 2.0f);
}

DynamicObject::DynamicObject(std::string spriteLoc, sf::IntRect spriteCut)
{
	if (!sf_texture.loadFromFile(spriteLoc, spriteCut)) {
		std::cout << "failed to load texture" << spriteLoc << std::endl;
	}

	sp_sprite.setTexture(sf_texture);

	sp_sprite.setOrigin(sf_texture.getSize().x / 2.0f, sf_texture.getSize().y / 2.0f);
}

void DynamicObject::Render(sf::RenderWindow& window)
{
	window.draw(sp_sprite);
	sp_sprite.setPosition(500, 500);
	sp_sprite.setScale(0.5,0.5);
}

void DynamicObject::Update()
{

}
