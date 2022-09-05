#include "MovingObjects/Enemies/RollingEnemy.h"

RollingEnemy::RollingEnemy()
    :Enemy(Objects::rollingEnemy, Direction::Left, Texture::enemies)
{
    m_moveSpeed = 150.f;
    m_velocity.x = -m_moveSpeed;
}

void RollingEnemy::update(sf::Time delta, Board& /*board*/)
{
    //dispose enemy after rolling ends:
    if (m_rolling && m_rollingClock.getElapsedTime().asSeconds() > rollingTime) {
        setDispose();
    }

    if (m_moveClock.getElapsedTime().asSeconds() > m_changeDirectionTime) {
        oppositeDirectionX();
        m_moveClock.restart();
    }

    m_animation.update(delta);
    m_prevLoc = m_sprite.getPosition();
    m_sprite.move(m_velocity * delta.asSeconds());
   
}

//makes the enemy crazy for a certain time before it disposed:
void RollingEnemy::setRolling()
{
    ResourcesManager::instance().playSound(Sound::enemy);
    m_rolling = true;
    m_velocity.x = 3.f * m_velocity.x; //move faster
    m_changeDirectionTime = 0.33f * m_changeDirectionTime;
    m_rollingClock.restart();
}


bool RollingEnemy::rolling() const
{
    return m_rolling;
}



bool RollingEnemy::m_registerit =
Factory<MovingObject>::registerit
(
    std::string(1, Symbol::rollingEnemy), []()->std::unique_ptr<MovingObject>
    { return std::make_unique<RollingEnemy>(); }
);
