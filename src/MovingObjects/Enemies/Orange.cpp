#include "MovingObjects/Enemies/Orange.h"

Orange::Orange()
    :Enemy(Objects::orange, Direction::Left, Texture::enemies)
{
    m_moveSpeed = 150.f;
    m_velocity.x = -m_moveSpeed;
}

void Orange::update(sf::Time delta, Board& /*board*/)
{
    if (m_clock.getElapsedTime().asSeconds() > TIME_GAP_ORANGE) {
        oppositeDirectionX();
        m_clock.restart();
    }

    m_animation.update(delta);
    m_prevLoc = m_sprite.getPosition();
    m_sprite.move(m_velocity * delta.asSeconds());

}

bool Orange::m_registerit =
Factory<MovingObject>::registerit
(
	std::string(1, Symbol::orange), []()->std::unique_ptr<MovingObject>
	{ return std::make_unique<Orange>(); }
);
