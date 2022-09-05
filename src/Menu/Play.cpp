#include "Menu/Play.h"
#include "Controller.h"

Play::Play(sf::RenderWindow& window)
	:m_window(window)
{
}


void Play::execute() {

	ResourcesManager::instance().stopMenuMusic();
	ResourcesManager::instance().playGameMusic();

	Controller controller(m_window);
	controller.runGame();

	ResourcesManager::instance().stopGameMusic();
	ResourcesManager::instance().playMenuMusic();

}