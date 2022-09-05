#include "StaticObjects/Bone.h"
#include "MovingObjects/Player.h"

Bone::Bone(sf::Vector2f position, Player& player)
	:StaticObject(Tiles::heart), //dummy
	m_animation(ResourcesManager::instance().getAnimationData(Objects::bone),
		Direction::Right, m_sprite, Texture::tileSet),
	m_player(player)
{
	m_sprite.setPosition(position); //spawn the bone in the player's position
	m_sprite.scale(0.65f, 0.65f);
	if (m_player.isFaceLeft()) {
		m_shootingDirection = Direction::Left;
	}
}

void Bone::update(sf::Time delta, Board& /*board*/)
{
	float direction = 1; //shoot right
	if (m_shootingDirection == Direction::Left) {
		direction = -1;
	}
	m_sprite.move(direction * delta.asSeconds() * shootingSpeed, 0.f);
	m_animation.update(sf::Time(sf::seconds(0.1f) + delta));

	//check in which direction to shoot:
	if ((m_shootingDirection == Direction::Right &&
		m_sprite.getPosition().x >= m_player.getPosition().x + shootingDistance)
		|| 
		(m_shootingDirection == Direction::Left &&
		m_sprite.getPosition().x <= m_player.getPosition().x - shootingDistance)) {
		setDispose();
	}
}
