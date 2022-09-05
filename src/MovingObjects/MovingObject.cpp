#include "MovingObjects/MovingObject.h"

MovingObject::MovingObject(Objects object, Direction direction, Texture texture)
    :m_animation(ResourcesManager::instance().getAnimationData(object),
        direction, m_sprite, texture)
{
    m_dir = direction;
}

Direction MovingObject::getDirection() const
{
    return m_dir;
}

void MovingObject::setDirection(sf::Keyboard::Key key)
{
    if (auto dir = toDirection(key))
    {
        m_dir = *dir;
        m_animation.setDirection(*dir);
    }
}

void MovingObject::setDirection(Direction dir)
{
    m_dir = dir;
}

void MovingObject::goBack()
{
    m_sprite.setPosition(m_prevLoc);
}

void MovingObject::oppositeDirectionX()
{
    m_velocity.x = -m_velocity.x; 
    m_dir = opposite(m_dir);
    m_animation.setDirection(m_dir);
}

void MovingObject::oppositeDirectionY()
{
    m_velocity.y = -m_velocity.y;
    m_dir = opposite(m_dir);
    m_animation.setDirection(m_dir);
}

sf::Vector2f MovingObject::getPrevLoc() const
{
    return m_prevLoc;
}

sf::Vector2f MovingObject::getVelocity() const
{
    return m_velocity;
}

void MovingObject::setVelocity(sf::Vector2f velocity)
{
    m_velocity = velocity;
}