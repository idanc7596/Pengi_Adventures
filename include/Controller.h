#pragma once 
#include "InfoBar.h"
#include "Board.h"
#include "MovingObjects/Player.h"
#include "MovingObjects/Enemies/Enemy.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>


class Controller
{
public:
	Controller(sf::RenderWindow& window);
	void runGame();
	void addMovingObject(std::unique_ptr<MovingObject> movingObject);
	void restartLevel();

private:
	void levelFlowControl(bool& m_gameRunning);
	void initLevel();
	void handleEvents();
	void updateObjects();
	void handleCollisions();
	void draw();
	void drawBackground();
	void resetView();
	void showTransitionScreen(sf::Sprite& screen);

	bool m_gameRunning = true; 
	sf::RenderWindow& m_window;
	sf::Sprite m_background;

	Board m_board;
	Player m_player;
	std::vector<std::unique_ptr<Enemy>> m_enemies;
	sf::Clock m_clock;


	InfoBar m_infoBar;
	int m_level = 1;
	const int numOfLevels = 3;
	const int numOfLives = 3;
	int m_formerLives = numOfLives;
	int m_currLives = numOfLives;

	//transition screens:
	sf::Sprite m_levelUpScreen;
	sf::Sprite m_lostScreen;
	sf::Sprite m_winScreen;
	const float messageScreenTime = 1.f;
	sf::Clock m_screenClock;
};
