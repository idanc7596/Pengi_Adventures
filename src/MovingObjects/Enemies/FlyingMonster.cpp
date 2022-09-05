#include "MovingObjects/Enemies/FlyingMonster.h"
#include "Direction.h"

FlyingMonster::FlyingMonster()
    :Enemy(Objects::flyingMonster, Direction::Left, Texture::enemies)
{
    m_moveSpeed = 120.f;
    m_velocity.x = -m_moveSpeed;
}

void FlyingMonster::update(sf::Time delta, Board& /*board*/)
{
    //change direction every certain time:
    if (m_clock.getElapsedTime().asSeconds() > TIME_GAP_MONSTER) {
        oppositeDirectionX();
        m_clock.restart();
    }

    m_animation.update(delta);
    m_prevLoc = m_sprite.getPosition();
    m_sprite.move(m_velocity * delta.asSeconds());
}


bool FlyingMonster::m_registerit =
Factory<MovingObject>::registerit
(
    std::string(1, Symbol::flyingMonster), []()->std::unique_ptr<MovingObject>
    { return std::make_unique<FlyingMonster>(); }
);

