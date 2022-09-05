#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <memory>
#include <optional>
#include <cstdlib>
#include "Command.h"
class Controller;

class Menu {
public:
	Menu();
	void show();

private:
	void handleEvents();
	void handleClick(sf::Vector2f clickPosition);
	void handleHover(sf::Vector2f hoverPosition);


	sf::RenderWindow m_window;
	sf::Sprite m_background;

	using button = std::pair<sf::Sprite&, std::unique_ptr<Command>>;
	std::vector<button> m_buttons;
	sf::Sprite m_playButton;
	sf::Sprite m_instructionsButton;
	sf::Sprite m_exitButton;
};