#include "UI.h"


UI::UI(std::string sf_font, sf::Vector2f pos, int size, std::string display)
{
	if (!font.loadFromFile("../assets/fonts/angry-birds.ttf")) {
		std::cout << "Failed to load font" << std::endl;
	}
	text.setFont(font);
	text.setCharacterSize(size);
	text.setPosition(pos);
	text.setString(display);
}

void UI::Render(sf::RenderWindow& window)
{
	window.draw(text);
}

void UI::Update()
{
}
