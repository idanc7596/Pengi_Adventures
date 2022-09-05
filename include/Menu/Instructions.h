#pragma once
#include "Command.h"
#include <SFML/Graphics.hpp>


class Instructions : public Command
{
public:
	Instructions(sf::RenderWindow& window);
	void execute() override;

private:

	sf::RenderWindow& m_window;
	sf::Sprite m_instructions;
	sf::Sprite m_backButton;
};