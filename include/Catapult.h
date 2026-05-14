#pragma once
#include "DynamicObject.h"
#include "Bird.h"

class Catapult : public DynamicObject {
private:
    sf::Vector2f catapultPos;//position of the catapult
    std::shared_ptr<Bird> loadedBird;//pointer of the bird that is in the catapult
    bool isDragging = false;
    sf::Vector2f dragStart;//starting position of the drag
    sf::Vector2f currentDrag;//current position of the drag
    const float MAX_DRAG = 100.f;//sets the dragback distance

public:
    Catapult() = default;
    Catapult(b2World& b2_world, b2Vec2 b2_posIn, std::string spriteLoc, sf::IntRect spriteCut) : DynamicObject(b2_world, b2_posIn, spriteLoc, spriteCut) {
        catapultPos = sf::Vector2f(b2_posIn.x * 30.f, b2_posIn.y * 30.f);//scales the catapult position

        b2_body->SetType(b2_staticBody);//sets the bodytype to static since itself doesnt need to move
    };
    ~Catapult() = default;

    void LoadBird(std::shared_ptr<Bird> bird);
    bool HandleInput(sf::Event& event, sf::RenderWindow& window);
    bool HasBird() { return loadedBird != nullptr; };
};
