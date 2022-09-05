#include "StaticObjects/Cannon.h"
#include "Board.h"

Cannon::Cannon() 
	:StaticObject(Tiles::cannon)
{
}

void Cannon::update(sf::Time /*delta*/, Board& board)
{
	//spawn bullet evey certain time:
	if (m_clock.getElapsedTime().asSeconds() > spawnTime) {
		spawnBullet(board);
		m_clock.restart();
	}
}

void Cannon::spawnBullet(Board& board)
{
	sf::Vector2f spawnPosition = { m_sprite.getPosition().x, m_sprite.getPosition().y - 0.79f*m_sprite.getGlobalBounds().height };
	auto bullet = std::make_unique<Bullet>(spawnPosition);
	board.addStaticObject(std::move(bullet));
}


bool Cannon::m_registerit =
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::cannon), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Cannon>(); }
);