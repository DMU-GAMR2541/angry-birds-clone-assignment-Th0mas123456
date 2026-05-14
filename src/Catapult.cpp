#include "Catapult.h"



void Catapult::LoadBird(std::shared_ptr<Bird> bird)
{
    loadedBird = bird;
    //if the bird is loaded then disables the collider on the catapult
    if (loadedBird) {
        this->getBody()->GetFixtureList()->SetSensor(true);
        loadedBird->getBody()->SetGravityScale(0);//sets the birds gravity to false
        loadedBird->getBody()->SetLinearVelocity(b2Vec2(0, 0));//sets the velocity to 0
        loadedBird->getBody()->SetTransform(b2Vec2(catapultPos.x / 30.f, catapultPos.y / 30.f), 0);//sets the loaded birds position to the catapult
    }
}

bool Catapult::HandleInput(sf::Event& event, sf::RenderWindow& window)
{
    if (!loadedBird) { return false; }

    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));//gets the mouse position in the window

    //if the left mouse is pressed then the bird follows the mouse position to show the dragging of the catapult
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f diff = mousePos - catapultPos;
            float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
            if (dist < 50.f) {
                isDragging = true;
                dragStart = catapultPos;
            }
        }
    }

    //when the mouse is moved and is dragging is true it calculates the drag distance so the speed can be altered by the amount you drag
    if (event.type == sf::Event::MouseMoved && isDragging) {
        sf::Vector2f drag = mousePos - dragStart;
        float dist = std::sqrt(drag.x * drag.x + drag.y * drag.y);
        //caps the drag distance
        if (dist > MAX_DRAG) {
            drag = drag / dist * MAX_DRAG;
        }
        currentDrag = drag;

        sf::Vector2f newPos = catapultPos + currentDrag;
        loadedBird->getBody()->SetTransform(b2Vec2(newPos.x / 30.f, newPos.y / 30.f), 0); //moves the bird to the dragged position
    }

    //on mouse release the bird is launched 
    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left && isDragging) {
            isDragging = false;
            float dragDist = std::sqrt(currentDrag.x * currentDrag.x + currentDrag.y * currentDrag.y);
            float dragPercent = dragDist / MAX_DRAG;
            float launchSpeed = loadedBird->getSpeed() * dragPercent; //only launches the bird as far as its dragged back
            sf::Vector2f launchDir = -currentDrag / dragDist;

            loadedBird->getBody()->SetGravityScale(1);//resets the bird so it has gravity again
            loadedBird->getBody()->ApplyLinearImpulse(b2Vec2(launchDir.x * launchSpeed, launchDir.y * launchSpeed),loadedBird->getBody()->GetWorldCenter(),true);//performs the actual launch

            loadedBird = nullptr;
            return true;
        }
    }
    return false;
}