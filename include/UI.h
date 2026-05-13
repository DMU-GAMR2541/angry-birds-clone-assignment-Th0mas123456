#pragma once
#include "StaticObject.h"
#include "DynamicObject.h"
#include <iostream>

class UI : public virtual StaticObject , public virtual DynamicObject{
private:
	sf::Text text;
	sf::Font font;
public:
	UI() = default;
	~UI() = default;
	UI(std::string sf_font, sf::Vector2f pos, int size, std::string display);
	void Render(sf::RenderWindow& window) override;
	void Update() override;
};