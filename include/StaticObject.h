#pragma once
#include "GameObject.h"

class StaticObject : public GameObject {
private:
    sf::Sprite sp_sprite;
    sf::Texture sf_texture;
public:
    StaticObject() = default;
    StaticObject(std::string spriteLoc, sf::IntRect spriteCut, sf::Vector2f position);
    StaticObject(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::Text text);
    virtual ~StaticObject() = default;
    void Render(sf::RenderWindow& window) override;
    void Update() override;
};

