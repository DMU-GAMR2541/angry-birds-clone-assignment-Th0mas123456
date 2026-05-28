#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "Pig.h"
#include "Bird.h"
#include <list>
#include <vector>
#include "UI.h"
#include "ContactListener.h"
#include "Walls.h"
#include "Catapult.h"

int main() {

    // --- 1. WINDOW SETUP ---
    sf::RenderWindow window(sf::VideoMode(800, 600), "Annoyed_Flocks");
    window.setFramerateLimit(60);

    //Box2D works in meters. SFML works in pixels.
    const float SCALE = 30.0f;

    //Can set a definition for PI.
    const float PI = 3.1415927;

    //setup world.
    b2Vec2 b2_gravity(0.0f, 9.8f); // Earth-like gravity
    b2World world(b2_gravity);

    //sets all the birds and pigs into a multimap
    std::multimap<std::string,std::shared_ptr<DynamicObject>> gameObjects;
    gameObjects.insert({ "bird",std::make_shared<Bird>(world, b2Vec2(100.f / SCALE, 500.f / SCALE), "../assets/Ang_Birds/Angry_Birds.png", sf::IntRect(902, 798, 47, 45), 50.f, 40.f, 20.f) });
    gameObjects.insert({ "bird",std::make_shared<Bird>(world, b2Vec2(150.f / SCALE, 500.f / SCALE), "../assets/Ang_Birds/Angry_Birds.png", sf::IntRect(667, 878, 61, 55), 50.f, 60.f, 30.f) });
    gameObjects.insert({ "bird",std::make_shared<Bird>(world, b2Vec2(200.f / SCALE, 500.f / SCALE), "../assets/Ang_Birds/Angry_Birds.png", sf::IntRect(408, 724, 64, 82), 50.f, 20.f, 50.f) });
    gameObjects.insert({ "pig", std::make_shared<Pig>(world, b2Vec2(550.f / SCALE, 500.f / SCALE), "../assets/Ang_Birds/Pigs.png", sf::IntRect(51, 66, 51, 51), 20.f) });
    gameObjects.insert({ "pig", std::make_shared<Pig>(world, b2Vec2(450.f / SCALE, 500.f / SCALE), "../assets/Ang_Birds/Pigs.png", sf::IntRect(50, 211, 96, 85), 30.f) });
    gameObjects.insert({ "pig",std::make_shared<Pig>(world, b2Vec2(550.f / SCALE, 370.f / SCALE), "../assets/Ang_Birds/Pigs.png", sf::IntRect(61, 417, 112, 100), 50.f) });
    
    //variable used later on so only one bird can be fired at once
    bool birdFired = false;

    //creates the catapult object
    Catapult catapult(world, b2Vec2(50.f / SCALE, 500.f / SCALE), "../assets/Ang_Birds/Angry_Birds.png", sf::IntRect(0, 0, 40, 167));

    //loads the first bird at the start
    auto it = gameObjects.find("bird");
    if (it != gameObjects.end()) {
        if (auto bird = std::dynamic_pointer_cast<Bird>(it->second)) {
            catapult.LoadBird(bird);
        }
    }

    //vector of wall objects
    std::vector < std::shared_ptr<Walls>> walls;
    walls.push_back(std::make_shared<Walls>(world, b2Vec2(500.f / SCALE, 500.0f / SCALE), sf::Vector2f(20.f, 100.f), sf::Color(255, 0, 0), b2_dynamicBody));
    walls.push_back(std::make_shared<Walls>(world, b2Vec2(600.f / SCALE, 500.0f / SCALE), sf::Vector2f(20.f, 100.f), sf::Color(255, 0, 0), b2_dynamicBody));
    walls.push_back(std::make_shared<Walls>(world, b2Vec2(550.f / SCALE, 390.0f / SCALE), sf::Vector2f(120.f, 20.f), sf::Color(255, 0, 0), b2_dynamicBody));


  
    //sets the UI of the pig count
    UI pigCount("../assets/fonts/angry-birds.ttf", sf::Vector2f(120.f,40.f), 24, "Pigs: " + std::to_string(gameObjects.count("pig")));

    //sets up the new contact listener
    ContactListener contactListener(gameObjects);
    world.SetContactListener(&contactListener);


    //Setup ground for the circle to move / bounce on.
    //Needs to have a body definition and a body. We use a raw pointer for the b2Body as Box2d does the management itself.
    //A body can be defined as having a position, velocity, and mass. 
    b2BodyDef b2_groundBodyDef;
    b2_groundBodyDef.position.Set(400.0f / SCALE, 590.0f / SCALE);
    b2Body* b2_groundBody = world.CreateBody(&b2_groundBodyDef);

    //Define a fixture shape that relates to the collision for the ground.
    b2PolygonShape b2_groundBox;
    b2_groundBox.SetAsBox(400.0f / SCALE, 10.0f / SCALE);
    b2_groundBody->CreateFixture(&b2_groundBox, 0.0f);

    //Set up the ground visualisation.
    sf::RectangleShape sf_groundVisual(sf::Vector2f(800.0f, 20.0f));
    sf_groundVisual.setOrigin(400.0f, 10.0f);
    sf_groundVisual.setFillColor(sf::Color(34, 139, 34)); // Forest Green

    ////Setting up a wall for the ball to hit.
    //b2BodyDef b2_wallDef;
    //b2_wallDef.position.Set(750.0f / SCALE, 500.0f / SCALE);
    //b2Body* b2_wallBody = world.CreateBody(&b2_wallDef);


    //b2PolygonShape b2_wallBox;
    //b2_wallBox.SetAsBox(10.0f / SCALE, 80.0f / SCALE);
    //b2_wallBody->CreateFixture(&b2_wallBox, 0.0f);

    //sf::RectangleShape sf_wallVisual(sf::Vector2f(20.0f, 160.0f));
    //sf_wallVisual.setOrigin(10.0f, 80.0f);
    //sf_wallVisual.setFillColor(sf::Color::Red);

    ////Rather than having an immovable wall, we can use the dynamic body type to create one that can have velocity etc.
    //b2BodyDef b2_plankDef;

    //b2_plankDef.type = b2_dynamicBody;
    //b2_plankDef.position.Set(550.0f / SCALE, 450.0f / SCALE);
    //b2Body* b2_plankBody = world.CreateBody(&b2_plankDef);

    //b2PolygonShape b2_plankBox;
    //b2_plankBox.SetAsBox(10.0f / SCALE, 60.0f / SCALE);

    //b2FixtureDef b2_plankFixture;
    //b2_plankFixture.shape = &b2_plankBox;
    //b2_plankFixture.density = 1.5f;   // Light wood
    //b2_plankFixture.friction = 0.3f;
    //b2_plankBody->CreateFixture(&b2_plankFixture);

    //sf::RectangleShape sf_plankVisual(sf::Vector2f(20.0f, 120.0f));
    //sf_plankVisual.setOrigin(10.0f, 60.0f);
    //sf_plankVisual.setFillColor(sf::Color(139, 69, 19)); // Brown

    ////Create a ball that is fired when space is pressed. We need to first have a dynamic ball to do it.
    //b2BodyDef b2_ballDef;
    //b2_ballDef.type = b2_dynamicBody;
    //b2_ballDef.position.Set(100.0f / SCALE, 500.0f / SCALE);
    //b2Body* b2_ballBody = world.CreateBody(&b2_ballDef);

    //b2CircleShape b2_circleShape;
    //b2_circleShape.m_radius = 15.0f / SCALE;

    //b2FixtureDef b2_ballFixture;
    //b2_ballFixture.shape = &b2_circleShape;
    //b2_ballFixture.density = 1.0f;
    //b2_ballFixture.restitution = 0.5f; // Bounciness
    //b2_ballBody->CreateFixture(&b2_ballFixture);

    //sf::CircleShape sf_ballVisual(15.0f);
    //sf_ballVisual.setOrigin(15.0f, 15.0f);
    //sf_ballVisual.setFillColor(sf::Color::Yellow);

    // --- 7. MAIN LOOP ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            //handles the input for the catapult
            if (catapult.HandleInput(event, window)) {
                birdFired = true;
            }

            // INPUT HANDLING: Press SPACE to launch
            //if (event.type == sf::Event::KeyPressed) {
            //    if (event.key.code == sf::Keyboard::Space) {
            //        // Reset position of the ball so that it can be fired again from its original poisition.
            //        b2_ballBody->SetTransform(b2Vec2(100.0f / SCALE, 500.0f / SCALE), 0);
            //        b2_ballBody->SetLinearVelocity(b2Vec2(0, 0));
            //        b2_ballBody->SetAngularVelocity(0);

            //        // Apply impulse (X-axis, Y-axis) Negative Y is UP in Box2D because gravity is positive.
            //        b2_ballBody->ApplyLinearImpulse(b2Vec2(5.0f, -5.0f), b2_ballBody->GetWorldCenter(), true);

            //        std::cout << "Firing!!!!" << std::endl;
            //    }
            //    else if (event.key.code == sf::Keyboard::A) {
            //        pig.getBody()->ApplyLinearImpulse(b2Vec2(5.0f, -5.0f), b2_ballBody->GetWorldCenter(), true);
            //    }

            //}
            // 
            //Input handling of the bird being launched
            //if (event.type == sf::Event::MouseButtonPressed) {
            //    if (event.mouseButton.button == sf::Mouse::Left && !gameObjects.empty()) {
            //        auto it = gameObjects.find("bird");
            //        if (it != gameObjects.end()) {
            //            // checks that the object being launched is a bird before launching
            //            if (auto bird = std::dynamic_pointer_cast<Bird>(it->second)) {
            //                bird->getBody()->ApplyLinearImpulse(b2Vec2(bird->getSpeed(), -bird->getSpeed()),bird->getBody()->GetWorldCenter(),true); // performs the launch
            //                birdFired = true; // sets fired to be true so that the check for the bird being destroyed can use it
            //            }
            //        }
            //    }
            //}
        }

        // Update Physics
        world.Step(1.0f / 60.0f, 8, 3);

        //checks if the bird has been fired then removes it once it has stopped moving then adds the next bird to the catapult
        if (birdFired && !gameObjects.empty()) {
            auto it = gameObjects.find("bird");
            if (it != gameObjects.end()) {
                if (auto bird = std::dynamic_pointer_cast<Bird>(it->second)) {
                    b2Vec2 velocity = bird->getBody()->GetLinearVelocity();
                    if (velocity.Length() < 0.1f || bird->getBody()->GetPosition().x * SCALE > window.getSize().x) {
                        gameObjects.erase(it);
                        birdFired = false;

                        auto next = gameObjects.find("bird");
                        if (next != gameObjects.end()) {
                            if (auto nextBird = std::dynamic_pointer_cast<Bird>(next->second)) {
                                catapult.LoadBird(nextBird);
                            }
                        }
                    }
                }
            }
        }

        //checks if the pigs are alive if not then it removes them
        for (auto it = gameObjects.begin(); it != gameObjects.end();) {
            if (auto pig = std::dynamic_pointer_cast<Pig>(it->second)) {
                if (pig->isDead()) {
                    world.DestroyBody(pig->getBody());
                    it = gameObjects.erase(it);
                }
                else {
                    ++it;
                }
            }
            else {
                ++it;
            }
        }

        //All of the visuals needs to be synced with the physics.

        /*sf_ballVisual.setPosition(b2_ballBody->GetPosition().x * SCALE, b2_ballBody->GetPosition().y * SCALE);
        sf_ballVisual.setRotation(b2_ballBody->GetAngle() * (180.0f / PI));*/

        //Static objects usually don't move, but we set the position once.
        sf_groundVisual.setPosition(b2_groundBody->GetPosition().x * SCALE, b2_groundBody->GetPosition().y * SCALE);
        //sf_wallVisual.setPosition(b2_wallBody->GetPosition().x * SCALE, b2_wallBody->GetPosition().y * SCALE);

        //// Dynamic wall.
        //sf_plankVisual.setPosition(b2_plankBody->GetPosition().x * SCALE, b2_plankBody->GetPosition().y * SCALE);
        //sf_plankVisual.setRotation(b2_plankBody->GetAngle() * (180.0f / PI));

        //Render all of the content at each frame. Remember you need to clear the screen each iteration or artefacts remain.
        window.clear(sf::Color(135, 206, 235)); // Sky Blue

        window.draw(sf_groundVisual);
        /*window.draw(sf_wallVisual);
        window.draw(sf_plankVisual);*/
        //window.draw(sf_ballVisual);

        //loop that handles the updating of the game objects
        for (auto& [key,obj] : gameObjects) {
            obj->Update();
        }
        //loop that renders all of the game objects
        for (auto& [key, obj] : gameObjects) {
            obj->Render(window);
        }
        //loop to render and update all the walls
        for (auto& w : walls) {
            w->Render(window);
            w->Update();
        }

        //displays and updates the pig count to the window
        pigCount.Render(window);
        pigCount.setText("Pigs: " + std::to_string(gameObjects.count("pig")));

        //renders and updates the catapult
        catapult.Update();
        catapult.Render(window);

        window.display();
    }
    
    return 0;
}