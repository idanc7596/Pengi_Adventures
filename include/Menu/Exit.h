#pragma once
#include "Command.h"
#include <SFML/Graphics.hpp>


class Exit : public Command
{
public:
	Exit(sf::RenderWindow& window);
	void execute() override;

private:
	sf::RenderWindow& m_window;
};