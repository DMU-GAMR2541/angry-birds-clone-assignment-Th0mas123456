#pragma once
#include "GameObject.h"
class DynamicObject : public GameObject{
private:
	sf::Sprite sp_sprite;
	sf::Texture sf_texture;
	b2Vec2 position;
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;

	b2Body* body;
	b2CircleShape dynamicCircle;
public:

	DynamicObject() = default;
	DynamicObject(std::string spriteLoc);
	DynamicObject(std::string spriteLoc, sf::IntRect spriteCut);
	virtual ~DynamicObject() = default;
	void Render(sf::RenderWindow& window);
	void Update();
};

