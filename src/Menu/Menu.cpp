#include "Menu/Menu.h"
#include "ResourcesManager.h"
#include "Controller.h"
#include "Menu/Command.h"
#include "Menu/Play.h"
#include "Menu/Instructions.h"
#include "Menu/Exit.h"
#include "macros.h"


Menu::Menu()
	:m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pengi Adventures", sf::Style::Close)
{
	m_window.setFramerateLimit(FPS);

	sf::Image icon;
	icon.loadFromFile("icon.png");
	m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	m_background.setTexture(ResourcesManager::instance().getTexture(Texture::menu));

	m_playButton.setTexture(ResourcesManager::instance().getTexture(Texture::tileSet));
	m_playButton.setTextureRect(ResourcesManager::instance().getTileRect(Tiles::play));
	m_playButton.setOrigin(m_playButton.getGlobalBounds().width / 2.f, m_playButton.getGlobalBounds().height / 2.f);
	m_playButton.setPosition({ WINDOW_WIDTH / 2.f, 230.f });

	m_instructionsButton.setTexture(ResourcesManager::instance().getTexture(Texture::tileSet));
	m_instructionsButton.setTextureRect(ResourcesManager::instance().getTileRect(Tiles::instructions));
	m_instructionsButton.setOrigin(m_instructionsButton.getGlobalBounds().width / 2.f, m_instructionsButton.getGlobalBounds().height / 2.f);
	m_instructionsButton.setPosition({ WINDOW_WIDTH / 2.f, 330.f });

	m_exitButton.setTexture(ResourcesManager::instance().getTexture(Texture::tileSet));
	m_exitButton.setTextureRect(ResourcesManager::instance().getTileRect(Tiles::exit));
	m_exitButton.setOrigin(m_exitButton.getGlobalBounds().width / 2.f, m_exitButton.getGlobalBounds().height / 2.f);
	m_exitButton.setPosition({ WINDOW_WIDTH / 2.f, 430.f });

	m_buttons.emplace_back(m_playButton, std::make_unique<Play>(m_window));
	m_buttons.emplace_back(m_instructionsButton, std::make_unique<Instructions>(m_window));
	m_buttons.emplace_back(m_exitButton, std::make_unique<Exit>(m_window));

}


void Menu::show()
{
	ResourcesManager::instance().playMenuMusic();

	while (m_window.isOpen()) {
		m_window.clear();
		m_window.draw(m_background);
		for (const auto& button : m_buttons) {
			m_window.draw(button.first);
		}
		m_window.display();

		handleEvents();
	}
}


void Menu::handleEvents()
{
	sf::Event ev;
	while (m_window.pollEvent(ev)) {
		if (ev.type == ev.Closed) {
			m_window.close();
			exit(EXIT_SUCCESS);
		}
		else if (ev.type == sf::Event::MouseButtonReleased) {
			sf::Vector2f clickPosition = m_window.mapPixelToCoords({ ev.mouseButton.x, ev.mouseButton.y });
			handleClick(clickPosition);
		}
		else if (ev.type == sf::Event::MouseMoved) {
			sf::Vector2f hoverPosition = m_window.mapPixelToCoords({ ev.mouseMove.x, ev.mouseMove.y });
			handleHover(hoverPosition);
		}
	}
}

void Menu::handleClick(sf::Vector2f clickPosition)
{
	for (unsigned i = 0; i < m_buttons.size(); i++) {
		if (m_buttons[i].first.getGlobalBounds().contains(clickPosition)) {
			ResourcesManager::instance().playSound(Sound::click);
			m_buttons[i].second->execute(); //execute the button operation
		}
	}
}

void Menu::handleHover(sf::Vector2f hoverPosition)
{
	for (const auto& button : m_buttons) {
		if (button.first.getGlobalBounds().contains(hoverPosition)) {
			button.first.setScale(1.1f, 1.1f);
		}
		else {
			button.first.setScale(1.f, 1.f);
		}
	}
}