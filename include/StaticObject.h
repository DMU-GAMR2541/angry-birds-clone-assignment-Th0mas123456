#pragma once
#include "GameObject.h"
class StaticObject : public GameObject {
private:
    sf::RectangleShape sf_shape;
public:
    StaticObject() = default;
    StaticObject(sf::Vector2f size, sf::Vector2f position, sf::Color color);
    virtual ~StaticObject() = default;
    void Render(sf::RenderWindow& window) override;
    void Update() override;
};

