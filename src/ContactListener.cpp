#include "ContactListener.h"

ContactListener::ContactListener(std::multimap<std::string, std::shared_ptr<DynamicObject>>& gameObjects) : gameObjects(gameObjects) {

}

void ContactListener::BeginContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    std::shared_ptr<Bird> bird = nullptr;
    std::shared_ptr<Pig> pig = nullptr;

    //checks which fixture is a bird and which is a pig
    for (auto& [key, obj] : gameObjects) {
        if (auto b = std::dynamic_pointer_cast<Bird>(obj)) {
            if (b->getBody() == bodyA || b->getBody() == bodyB) {
                bird = b;
            }
        }
        if (auto p = std::dynamic_pointer_cast<Pig>(obj)) {
            if (p->getBody() == bodyA || p->getBody() == bodyB) {
                pig = p;
            }
        }
    }

    if (bird != nullptr && pig != nullptr) {
        pig->takeDamage(bird->getDamage());
    }
}