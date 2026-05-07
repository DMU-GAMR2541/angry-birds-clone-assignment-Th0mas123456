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

DynamicObject::DynamicObject(b2World& b2_world, b2Vec2 b2_posIn,std::string spriteLoc, sf::IntRect spriteCut)
{
	if (!sf_texture.loadFromFile(spriteLoc, spriteCut)) {
		std::cout << "failed to load texture" << spriteLoc << std::endl;
	}

	sp_sprite.setTexture(sf_texture);

	sp_sprite.setOrigin(sf_texture.getSize().x / 2.0f, sf_texture.getSize().y / 2.0f);
	
	b2_bodyDef.type = b2_dynamicBody;
	b2_bodyDef.position = b2_posIn;

	b2_body = b2_world.CreateBody(&b2_bodyDef);


	b2_dynamicCircle.m_radius = (sf_texture.getSize().x / 2.0f) / SCALE;
	//Setup Fixture.
	b2_fixtureDef.shape = &b2_dynamicCircle;
	b2_fixtureDef.density = 1.0f;
	b2_fixtureDef.friction = 0.3f;
	b2_fixtureDef.restitution = 0.5f;

	// Attach to body.
	b2_body->CreateFixture(&b2_fixtureDef);
}

void DynamicObject::Render(sf::RenderWindow& window)
{
	window.draw(sp_sprite);
}

void DynamicObject::Update()
{
	b2Vec2 pos = b2_body->GetPosition();
	sp_sprite.setPosition(pos.x * SCALE, pos.y * SCALE);
	sp_sprite.setRotation(b2_body->GetAngle() * (180.f / PI));
}
