#include "Menu/Instructions.h"
#include "ResourcesManager.h"

Instructions::Instructions(sf::RenderWindow& window)
	:  m_window(window)
{
	m_instructions.setTexture(ResourcesManager::instance().getTexture(Texture::instructions));

	m_backButton.setTexture(ResourcesManager::instance().getTexture(Texture::tileSet));
	m_backButton.setTextureRect(ResourcesManager::instance().getTileRect(Tiles::back));
	m_backButton.setOrigin(m_backButton.getGlobalBounds().width / 2.f, m_backButton.getGlobalBounds().height / 2.f);
	m_backButton.setPosition({ 1030.f, 550.f });
}


void Instructions::execute()
{

	bool displayInstructions = true;

	while (displayInstructions) {

		m_window.clear();
		m_window.draw(m_instructions);
		m_window.draw(m_backButton);
		m_window.display();

		sf::Event ev;
		while (m_window.pollEvent(ev)) {

			if (ev.type == ev.Closed) {
				m_window.close();
				exit(EXIT_SUCCESS);
			}
			else if (ev.type == sf::Event::MouseButtonReleased) {
				sf::Vector2f clickPosition =
					m_window.mapPixelToCoords({ ev.mouseButton.x, ev.mouseButton.y });
				if (m_backButton.getGlobalBounds().contains(clickPosition)) {
					ResourcesManager::instance().playSound(Sound::click);
					displayInstructions = false;
					break;
				}
			}
			else if (ev.type == sf::Event::MouseMoved) {
				sf::Vector2f hoverPosition = m_window.mapPixelToCoords({ ev.mouseMove.x, ev.mouseMove.y });
				if (m_backButton.getGlobalBounds().contains(hoverPosition)) {
					m_backButton.setScale(1.1f, 1.1f);
				}
				else {
					m_backButton.setScale(1.f, 1.f);
				}
			}

		}

	}

}