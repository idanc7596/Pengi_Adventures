#include "StaticObjects/Bullet.h"

Bullet::Bullet(sf::Vector2f position)
	: StaticObject(Tiles::bullet)
{
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height/2.f);
	m_sprite.setPosition(position);
}

void Bullet::update(sf::Time delta, Board& /*board*/)
{
	m_sprite.move({ delta.asSeconds() * -moveSpeed, 0.f });
	m_distancePassed += std::abs(delta.asSeconds() * -moveSpeed);

	if (m_distancePassed >= maxDistance) {
		setDispose();
	}
}
