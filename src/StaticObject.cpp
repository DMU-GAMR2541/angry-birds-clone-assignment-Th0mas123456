#include "StaticObject.h"
#include <iostream>

StaticObject::StaticObject(std::string spriteLoc, sf::IntRect spriteCut, sf::Vector2f position)
{
	if (!sf_texture.loadFromFile(spriteLoc, spriteCut)) {
		std::cout << "failed to load texture" << spriteLoc << std::endl;
	}

	sp_sprite.setTexture(sf_texture);
	sp_sprite.setOrigin(sf_texture.getSize().x / 2.0f, sf_texture.getSize().y / 2.0f);
	sp_sprite.setPosition(position);
}

StaticObject::StaticObject(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::Text text)
{
}

void StaticObject::Render(sf::RenderWindow& window)
{
    window.draw(sp_sprite);
}

void StaticObject::Update()
{}
