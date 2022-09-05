#pragma once
#include "Command.h"
#include <SFML/Graphics.hpp>


class Play : public Command
{
public:
	Play(sf::RenderWindow& window);
	void execute() override;

private:
	sf::RenderWindow& m_window;

};
