#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class InfoBar {
public:
	InfoBar();
	void draw(sf::RenderWindow& window) const;
	void updatePosition(sf::Vector2f viewCenter);
	void update(int level, int score, int lives);
	void resetHearts();

private:
	sf::Text m_level;
	sf::Text m_score;
	sf::Text m_lives;
	int m_livesNumber = numOfLives;
	std::vector<sf::Sprite> m_hearts; //for lives

	const float gap = 100.f; 
	const int numOfLives = 3;
};