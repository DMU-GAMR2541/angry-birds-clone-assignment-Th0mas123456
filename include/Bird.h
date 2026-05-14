#pragma once
#include "DynamicObject.h"
class Bird : public DynamicObject{
private:
	float birdSpeed;
	float birdMass;
	float birdDamage;
public:
	Bird() = default;
	Bird(std::string spriteLoc) : DynamicObject(spriteLoc) {};
	Bird(b2World& b2_world, b2Vec2 b2_posIn, std::string spriteLoc, sf::IntRect spriteCut, float mass, float speed, float damage) : DynamicObject(b2_world, b2_posIn, spriteLoc, spriteCut) {
		birdSpeed = speed;
		birdMass = mass;
		birdDamage = damage;
	};
	~Bird() = default;
	float getSpeed() { return birdSpeed; };
	float getDamage() { return birdDamage; };
};

