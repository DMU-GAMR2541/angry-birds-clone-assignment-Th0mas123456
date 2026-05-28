#include <gtest/gtest.h>
#include "Enemy.h"
#include "Slingshot.h"
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "Bird.h"
#include "Pig.h"
#include "Walls.h"

/// <summary>
///Taken from the GoogleTest primer. 
/// </summary>

// The fixture for testing class Foo.
//class EnemyTest : public testing::Test {
//public:
//    std::unique_ptr<Enemy> enemy;
//protected:
//    // You can remove any or all of the following functions if their bodies would
//    // be empty.
//
//    EnemyTest() {
//        // You can do set-up work for each test here.
//                    
//    }
//
//    ~EnemyTest() override {
//        // You can do clean-up work that doesn't throw exceptions here.
//    }
//
//    // If the constructor and destructor are not enough for setting up
//    // and cleaning up each test, you can define the following methods:
//
//    void SetUp() override {
//        // Code here will be called immediately after the constructor (right
//        // before each test).
//        enemy = std::make_unique<Enemy>(50); // All enemnies in this test suite start with 50 HP.
//                    
//    }
//
//    void TearDown() override {
//        // Code here will be called immediately after each test (right
//        // before the destructor).
//    }
//
//
//};
//
//class SlingTest : public testing::Test {
//public:
//    std::unique_ptr<Slingshot> sling;
//protected:
//    // You can remove any or all of the following functions if their bodies would
//    // be empty.
//
//    SlingTest() {
//        // You can do set-up work for each test here.
//
//    }
//
//    ~SlingTest() override {
//        // You can do clean-up work that doesn't throw exceptions here.
//    }
//
//    // If the constructor and destructor are not enough for setting up
//    // and cleaning up each test, you can define the following methods:
//
//    void SetUp() override {
//        // Code here will be called immediately after the constructor (right
//        // before each test).
//        sling = std::make_unique<Slingshot>();
//    }
//
//    void TearDown() override {
//        // Code here will be called immediately after each test (right
//        // before the destructor).
//    }
//
//
//};
//
////A single test, not a fixture. No setup is called.
//TEST(Enemy, First_test) {
//    Enemy e(100);
//    EXPECT_GE(e.getHealth(), 100);
//    //SUCCEED() << "Test test passed";
//    //FAIL() << "Test didn't pass";
//}
//
//TEST_F(EnemyTest, LethalDamagePopsPig) {
//    enemy->takeDamage(60);
//    EXPECT_TRUE(enemy->checkIfPopped());
//}
//
//TEST_F(EnemyTest, NonLeathalDamage) {
//    enemy->takeDamage(40);
//    EXPECT_FALSE(enemy->checkIfPopped());
//}
//
//TEST_F(SlingTest, tensionStart) {
//    EXPECT_EQ(sling->getTension(), 0);
//}
//
//TEST_F(SlingTest, slingCycle) {
//    sling->pullBack(100);
//    EXPECT_EQ(sling->getTension(), 100);
//}
//
//TEST_F(SlingTest, slingRelease) {
//    sling->pullBack(100);
//    sling->release();
//    EXPECT_EQ(sling->getTension(), 0);
//}

class GameObjectTest : public ::testing::Test {
protected:
    b2World* world;
    const float SCALE = 30.0f;

    void SetUp() override {
        world = new b2World(b2Vec2(0.0f, 9.8f));
    }

    void TearDown() override {
        delete world;
        world = nullptr;
    }
};


//test for a successful sprite loading
TEST_F(GameObjectTest, Texture_LoadsSuccessfully) {
    sf::Texture texture;
    bool loaded = texture.loadFromFile("../assets/Ang_Birds/Pigs.png",
    sf::IntRect(51, 66, 51, 51));
    EXPECT_TRUE(loaded);
}


//test for a sprite failing to load
TEST_F(GameObjectTest, Texture_FailsWithInvalidPath) {
    sf::Texture texture;
    bool loaded = texture.loadFromFile("failed.png");
    EXPECT_FALSE(loaded);
}


//test that the pig shouldn't die if it doesnt take enough damage
TEST_F(GameObjectTest, Pig_TakesDamage_HealthReduces) {
    Pig pig(*world, b2Vec2(100.f / SCALE, 500.f / SCALE),"../assets/Ang_Birds/Pigs.png", sf::IntRect(51, 66, 51, 51), 100.f);

    pig.takeDamage(30.f);
    EXPECT_FALSE(pig.isDead());
}


//tests that the pig will die if it takes enough damage
TEST_F(GameObjectTest, Pig_Dies_WhenHealthReachesZero) {
    Pig pig(*world, b2Vec2(100.f / SCALE, 500.f / SCALE),"../assets/Ang_Birds/Pigs.png", sf::IntRect(51, 66, 51, 51), 20.f);

    pig.takeDamage(20.f);
    EXPECT_TRUE(pig.isDead());
}


//tests that the pig doesnt die when nothing happens to it
TEST_F(GameObjectTest, Pig_NotDead_WithFullHealth) {
    Pig pig(*world, b2Vec2(100.f / SCALE, 500.f / SCALE),"../assets/Ang_Birds/Pigs.png", sf::IntRect(51, 66, 51, 51), 50.f);

    EXPECT_FALSE(pig.isDead());
}


//tests if the birds movement is correct as low speeds
TEST_F(GameObjectTest, DynamicObject_MovesCorrectly_LowSpeed) {
    Bird bird(*world, b2Vec2(100.f / SCALE, 500.f / SCALE),"../assets/Ang_Birds/Angry_Birds.png", sf::IntRect(902, 798, 47, 45), 50.f, 5.f, 5.f);

    bird.getBody()->ApplyLinearImpulse(b2Vec2(5.f, 0.f), bird.getBody()->GetWorldCenter(), true);
    world->Step(1.f / 60.f, 8, 3);

    EXPECT_GT(bird.getBody()->GetPosition().x, 100.f / SCALE);
}

//tests if the birds movement is correct at medium speeds
TEST_F(GameObjectTest, DynamicObject_MovesCorrectly_MediumSpeed) {
    Bird bird(*world, b2Vec2(100.f / SCALE, 500.f / SCALE),"../assets/Ang_Birds/Angry_Birds.png", sf::IntRect(902, 798, 47, 45), 50.f, 15.f, 15.f);

    bird.getBody()->ApplyLinearImpulse(b2Vec2(15.f, 0.f), bird.getBody()->GetWorldCenter(), true);
    world->Step(1.f / 60.f, 8, 3);

    EXPECT_GT(bird.getBody()->GetPosition().x, 100.f / SCALE);
}

//tests if the birds movement is correct at high speeds
TEST_F(GameObjectTest, DynamicObject_MovesCorrectly_HighSpeed) {
    Bird bird(*world, b2Vec2(100.f / SCALE, 500.f / SCALE),"../assets/Ang_Birds/Angry_Birds.png", sf::IntRect(902, 798, 47, 45), 50.f, 50.f, 50.f);

    bird.getBody()->ApplyLinearImpulse(b2Vec2(50.f, 0.f), bird.getBody()->GetWorldCenter(), true);
    world->Step(1.f / 60.f, 8, 3);

    EXPECT_GT(bird.getBody()->GetPosition().x, 100.f / SCALE);
}

//tests if gravity works correctly on the bird
TEST_F(GameObjectTest, DynamicObject_FallsWithGravity) {
    Bird bird(*world, b2Vec2(100.f / SCALE, 100.f / SCALE),"../assets/Ang_Birds/Angry_Birds.png", sf::IntRect(902, 798, 47, 45), 50.f, 10.f, 10.f);

    float initialY = bird.getBody()->GetPosition().y;
    world->Step(1.f / 60.f, 8, 3);

    EXPECT_GT(bird.getBody()->GetPosition().y, initialY);
}


//tests if 2 pigs are in different positions relative to eachother
TEST_F(GameObjectTest, Pig_PositionCorrect_RelativeToOtherPigs_1) {
    Pig pig1(*world, b2Vec2(100.f / SCALE, 500.f / SCALE),"../assets/Ang_Birds/Pigs.png", sf::IntRect(51, 66, 51, 51), 20.f);
    Pig pig2(*world, b2Vec2(200.f / SCALE, 500.f / SCALE),"../assets/Ang_Birds/Pigs.png", sf::IntRect(51, 66, 51, 51), 20.f);

    EXPECT_LT(pig1.getBody()->GetPosition().x, pig2.getBody()->GetPosition().x);
}


//tests if 3 pigs are in different positions relative to eachother
TEST_F(GameObjectTest, Pig_PositionCorrect_RelativeToOtherPigs_2) {
    Pig pig1(*world, b2Vec2(100.f / SCALE, 500.f / SCALE),"../assets/Ang_Birds/Pigs.png", sf::IntRect(51, 66, 51, 51), 20.f);
    Pig pig2(*world, b2Vec2(200.f / SCALE, 500.f / SCALE),"../assets/Ang_Birds/Pigs.png", sf::IntRect(51, 66, 51, 51), 20.f);
    Pig pig3(*world, b2Vec2(300.f / SCALE, 500.f / SCALE),"../assets/Ang_Birds/Pigs.png", sf::IntRect(51, 66, 51, 51), 20.f);

    EXPECT_LT(pig2.getBody()->GetPosition().x, pig3.getBody()->GetPosition().x);
}

//tests if the bird is in a different position relative to the pig
TEST_F(GameObjectTest, Bird_PositionCorrect_RelativeToPig) {
    Bird bird(*world, b2Vec2(100.f / SCALE, 500.f / SCALE),"../assets/Ang_Birds/Angry_Birds.png", sf::IntRect(902, 798, 47, 45), 50.f, 10.f, 10.f);
    Pig pig(*world, b2Vec2(400.f / SCALE, 500.f / SCALE),"../assets/Ang_Birds/Pigs.png", sf::IntRect(51, 66, 51, 51), 20.f);

    EXPECT_LT(bird.getBody()->GetPosition().x, pig.getBody()->GetPosition().x);
}

//tests if the pig is in a different position relative to the wall object
TEST_F(GameObjectTest, Bird_PositionCorrect_RelativeToWall) {
    Bird bird(*world, b2Vec2(100.f / SCALE, 500.f / SCALE),"../assets/Ang_Birds/Angry_Birds.png", sf::IntRect(902, 798, 47, 45), 50.f, 10.f, 10.f);
    Walls wall(*world, b2Vec2(600.f / SCALE, 500.f / SCALE),sf::Vector2f(20.f, 100.f), sf::Color::Red, b2_staticBody);

    EXPECT_LT(bird.getBody()->GetPosition().x, wall.getBody()->GetPosition().x);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}