#include "ContactListener.h"

ContactListener::ContactListener(std::multimap<std::string, std::shared_ptr<DynamicObject>>& gameObjects) : gameObjects(gameObjects){

}

void ContactListener::BeginContact(b2Contact* contact){

    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    for (auto& [key, obj] : gameObjects) {
        if (auto pig = std::dynamic_pointer_cast<Pig>(obj)) {
            if (pig->getBody() == bodyA || pig->getBody() == bodyB) {
                pig->takeDamage(10.f);
            }
        }
    }
}
