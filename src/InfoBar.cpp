#include "InfoBar.h"
#include "ResourcesManager.h"
#include "macros.h"
#include <iostream>

InfoBar::InfoBar()
{
	m_level.setFont(ResourcesManager::instance().getFont(Font::infoBarFont));
	m_level.setCharacterSize(33);
	m_level.setFillColor(sf::Color::White);
	m_level.setOutlineThickness(1.5f);
	m_level.setOutlineColor(sf::Color::Black);
	m_level.setPosition(13.f, 8.f);
	m_level.setString("Level: 1");

	m_score.setFont(ResourcesManager::instance().getFont(Font::infoBarFont));
	m_score.setCharacterSize(33);
	m_score.setFillColor(sf::Color::White);
	m_score.setOutlineThickness(1.5f);
	m_score.setOutlineColor(sf::Color::Black);
	m_score.setString("Score: 0");
	sf::Vector2f scorePosition(
		m_level.getPosition().x + m_level.getGlobalBounds().width + gap,
		m_level.getPosition().y);
	m_score.setPosition(scorePosition);

	m_lives.setFont(ResourcesManager::instance().getFont(Font::infoBarFont));
	m_lives.setCharacterSize(33);
	m_lives.setFillColor(sf::Color::White);
	m_lives.setOutlineThickness(1.5f);
	m_lives.setOutlineColor(sf::Color::Black);
	m_lives.setString("Lives: ");
	sf::Vector2f livesPosition(
		m_score.getPosition().x + m_score.getGlobalBounds().width + gap,
		m_score.getPosition().y);
	m_lives.setPosition(livesPosition);

	resetHearts();

}

void InfoBar::update(int level, int score, int lives)
{
	m_level.setString("Level: " + std::to_string(level));
	m_score.setString("Score: " + std::to_string(score));
	m_livesNumber = lives;
	
	m_hearts.resize(m_livesNumber); 
}

void InfoBar::resetHearts()
{
	m_hearts.clear();

	sf::Vector2f livesPosition(
		m_score.getPosition().x + m_score.getGlobalBounds().width + gap,
		m_score.getPosition().y);
	sf::Vector2f heartPosition(livesPosition.x + m_lives.getGlobalBounds().width,
		livesPosition.y + 2.3f);
	for (int i = 0; i < numOfLives; i++) {
		sf::Sprite heart(ResourcesManager::instance().getTexture(Texture::tileSet));
		heart.setTextureRect(ResourcesManager::instance().getTileRect(Tiles::heart));
		heart.scale(0.65f, 0.65f);
		heart.setPosition(heartPosition);
		heartPosition.x += heart.getGlobalBounds().width + 3.f;
		m_hearts.push_back(heart);
	}
}

void InfoBar::draw(sf::RenderWindow& window) const
{
	window.draw(m_level);
	window.draw(m_score);
	window.draw(m_lives);
	for (auto& heart : m_hearts) {
		window.draw(heart);
	}
}

//update the infobar posision according to the view:
void InfoBar::updatePosition(sf::Vector2f viewCenter)
{
	sf::Vector2f levelPosition(viewCenter.x - WINDOW_WIDTH / 2.f + 13.f,
		viewCenter.y - WINDOW_HEIGHT / 2.f + 8.f);
	m_level.setPosition(levelPosition);

	sf::Vector2f scorePosition(levelPosition.x + m_level.getGlobalBounds().width + gap,
		levelPosition.y);
	m_score.setPosition(scorePosition);

	sf::Vector2f livesPosition(scorePosition.x + m_score.getGlobalBounds().width + gap,
		scorePosition.y);
	m_lives.setPosition(livesPosition);

	sf::Vector2f heartPosition(livesPosition.x + m_lives.getGlobalBounds().width,
		livesPosition.y + 2.3f);
	for (auto& heart : m_hearts) {
		heart.setPosition(heartPosition);
		heartPosition.x += heart.getGlobalBounds().width + 3.f;
	}
}

