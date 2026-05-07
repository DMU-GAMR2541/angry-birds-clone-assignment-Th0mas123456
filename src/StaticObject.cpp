#include "StaticObject.h"

StaticObject::StaticObject(sf::Vector2f size, sf::Vector2f position, sf::Color color)
{
    sf_shape.setSize(size);
    sf_shape.setOrigin(size.x / 2.0f, size.y / 2.0f);
    sf_shape.setPosition(position);
    sf_shape.setFillColor(color);
}

void StaticObject::Render(sf::RenderWindow& window)
{
    window.draw(sf_shape);
}

void StaticObject::Update()
{}
