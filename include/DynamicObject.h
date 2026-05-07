#pragma once
#include "GameObject.h"
class DynamicObject : public GameObject{
private:
	sf::Sprite sp_sprite;
	sf::Texture sf_texture;
	b2Vec2 b2_position;
	b2BodyDef b2_bodyDef;
	b2FixtureDef b2_fixtureDef;

	b2Body* b2_body;
	b2CircleShape b2_dynamicCircle;

	float SCALE = 30.0f;
	const float PI = 3.1415927;
public:
	DynamicObject() = default;
	DynamicObject(std::string spriteLoc);
	DynamicObject(b2World& b2_world, b2Vec2 b2_posIn,std::string spriteLoc, sf::IntRect spriteCut);
	virtual ~DynamicObject() = default;
	void Render(sf::RenderWindow& window) override;
	void Update();
	b2Body* getBody() { return b2_body; };
};

