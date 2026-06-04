#pragma once
#include <SFML/Graphics.hpp>
#include <future>
#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>

class LoadScreen {
private:
    sf::RectangleShape loadingBar;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Text loadingText;
    sf::Font font;

    std::mutex progressMutex;
    float loadProgress = 0.f;
    std::future<void> loadingFuture;

    void loadSprites() {
        for (int i = 0; i <= 50; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
            std::lock_guard<std::mutex> lock(progressMutex);
            loadProgress = static_cast<float>(i);
            std::cout << "Sprites loading: " << i << "%" << std::endl;
        }
    }

    void loadPhysics() {
        for (int i = 50; i <= 100; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
            std::lock_guard<std::mutex> lock(progressMutex);
            loadProgress = static_cast<float>(i);
            std::cout << "Physics loading: " << i << "%" << std::endl;
        }
    }

public:
    LoadScreen(sf::Vector2u windowSize) {

        if (!backgroundTexture.loadFromFile("../assets/Ang_Birds/splash.png")) {
            std::cout << "Failed to load background texture" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(static_cast<float>(windowSize.x) / static_cast<float>(backgroundTexture.getSize().x),static_cast<float>(windowSize.y) / static_cast<float>(backgroundTexture.getSize().y));


        loadingBar.setPosition(0.f, windowSize.y / 2.f);
        loadingBar.setFillColor(sf::Color::Green);
        loadingBar.setSize(sf::Vector2f(0.f, 30.f));


        if (!font.loadFromFile("../assets/fonts/angry-birds.ttf")) {
            std::cout << "Failed to load font" << std::endl;
        }
        loadingText.setFont(font);
        loadingText.setCharacterSize(24);
        loadingText.setFillColor(sf::Color::White);
        loadingText.setString("Loading...");
        loadingText.setPosition(windowSize.x / 2.f - 50.f,windowSize.y / 2.f - 40.f);

        loadingFuture = std::async(std::launch::async, [this]() {loadSprites();loadPhysics();});
    }


    bool isComplete() {
        return loadingFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
    }

    float getProgress() {
        std::lock_guard<std::mutex> lock(progressMutex);
        return loadProgress;
    }

    void Update(sf::Vector2u windowSize) {
        float progress = getProgress();
        loadingBar.setSize(sf::Vector2f(progress / 100.f * windowSize.x, 30.f));
        loadingText.setString("Loading... " + std::to_string(static_cast<int>(progress)) + "%");
    }

    void Render(sf::RenderWindow& window) {
        window.draw(backgroundSprite);
        window.draw(loadingBar);
        window.draw(loadingText);
    }
};