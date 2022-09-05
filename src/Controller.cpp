#include "Controller.h"
#include "macros.h"
#include "CollisionHandling.h"
#include <cstdlib>

Controller::Controller(sf::RenderWindow& window)
	: m_window(window),
	m_infoBar(),
	m_board(*this),
	m_player(),
	m_levelUpScreen(ResourcesManager::instance().getTexture(Texture::levelUp)),
	m_lostScreen(ResourcesManager::instance().getTexture(Texture::lost)),
	m_winScreen(ResourcesManager::instance().getTexture(Texture::win))
{
	m_background.setTexture(ResourcesManager::instance().getTexture(Texture::background));
	m_background.setOrigin(0, 0.4f * m_background.getGlobalBounds().height);
}

void Controller::runGame()
{
	while (m_gameRunning) { //game loop
		
		initLevel();

		while (m_gameRunning && !m_player.win()) { //level loop
			m_infoBar.update(m_level, m_player.getScore(), m_player.getLives());
			handleEvents();
			updateObjects();
			handleCollisions();
			draw();
			levelFlowControl(m_gameRunning);
		}

		if (m_gameRunning) {
			if (m_level < numOfLevels) {
				m_level++;
				ResourcesManager::instance().playSound(Sound::levelUp);
				showTransitionScreen(m_levelUpScreen);
			}
			else {
				ResourcesManager::instance().playSound(Sound::win);
				showTransitionScreen(m_winScreen);
				m_gameRunning = false;
			}
		}	

	}
}

void Controller::initLevel()
{
	m_player.resetForNewLevel();
	m_formerLives = m_currLives = numOfLives;
	m_enemies.clear(); //the order is important!
	m_board.readLevelFromFile(m_level);
	m_infoBar.resetHearts();
	resetView();
}

//checks if we need to restart the level:
void Controller::levelFlowControl(bool& gameRunning)
{
	m_currLives = m_player.getLives();
	if (m_currLives == m_formerLives - 1) {
		if (m_currLives > 0) {
			restartLevel();
		}
		else {
			ResourcesManager::instance().playSound(Sound::lose);
			showTransitionScreen(m_lostScreen);
			gameRunning = false;
		}
	}
	m_formerLives = m_currLives;
}


void Controller::restartLevel()
{
	m_player.resetForRestartLevel();
	m_enemies.clear(); 
	m_board.readLevelFromFile(m_level);
	resetView();
}


void Controller::handleEvents()
{
	sf::Event ev;
	while (m_window.pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed:
			m_window.close();
			exit(EXIT_SUCCESS);
			break;
		case sf::Event::KeyPressed:
			m_player.setDirection(ev.key.code);
			break;
		default:
			break;
		}
	}
}

void Controller::updateObjects()
{
	sf::Time deltaTime = m_clock.restart();

	m_player.update(deltaTime, m_board);
	for (auto& enemy : m_enemies) {
		enemy->update(deltaTime, m_board);
	}

	//erase disposed enemies:
	std::erase_if(m_enemies, [](const auto& enemy) {
		return enemy->dispose();
		});

	m_board.update(deltaTime);
}

void Controller::handleCollisions()
{
	//player with static objects:
	int numOfStaticObjects = m_board.getNumOfStaticObjects();
	for(int i = 0; i < numOfStaticObjects; i++) {
		processCollision(m_player, m_board.getStaticObject(i));
	}

	//player with enemies:
	for (auto& enemy : m_enemies) {
		processCollision(m_player, *enemy);
	}

	//enemies with static objects:
	for (int i = 0; i < numOfStaticObjects; i++) {
		for (auto& enemy : m_enemies) {
			processCollision(*enemy, m_board.getStaticObject(i));
		}
	}
}

void Controller::draw()
{
	//update the view only after player passed the first half of the screen:
	if (m_player.getPosition().x >= WINDOW_WIDTH / 2.f) {
		sf::View view({ m_player.getPosition().x, WINDOW_HEIGHT/2.f},
			{WINDOW_WIDTH, WINDOW_HEIGHT});
		m_window.setView(view);
		m_infoBar.updatePosition(view.getCenter());
	}
	
	m_window.clear(sf::Color::White);
	drawBackground();

	m_board.draw(m_window);
	m_player.draw(m_window);
	for (auto& enemy : m_enemies) {
		enemy->draw(m_window);
	}

	m_infoBar.draw(m_window);
	m_window.display();
}

void Controller::drawBackground()
{
	//duplicate the background along the level width (for view):
	for (int i = 0; i < BACKGROUND_FRAMES; i++) {
		m_window.draw(m_background);
		m_background.setPosition(i * m_background.getGlobalBounds().width, 0);
	}
}

//the board calls this function in order to add moving objects to the controller:
void Controller::addMovingObject(std::unique_ptr<MovingObject> movingObject)
{
	MovingObject* mo = movingObject.release();
	if (Enemy* e = dynamic_cast<Enemy*>(mo)) {
		std::unique_ptr<Enemy> uq(e);
		m_enemies.push_back(std::move(uq));
	}
}

void Controller::resetView()
{
	sf::View view({ WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f },
		{ WINDOW_WIDTH, WINDOW_HEIGHT });
	m_window.setView(view);
	m_infoBar.updatePosition(view.getCenter());
}

void Controller::showTransitionScreen(sf::Sprite& screen)
{
	resetView();
	m_screenClock.restart();

	while (m_screenClock.getElapsedTime().asSeconds() < messageScreenTime) {
		m_window.clear();
		m_window.draw(screen);
		m_window.display();
	}

	m_clock.restart();
}


