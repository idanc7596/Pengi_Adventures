#include "StaticObjects/Escalator.h"

Escalator::Escalator()
    :StaticObject(Tiles::escalator)
{

}

void Escalator::update(sf::Time delta, Board& /*board*/)
{
    if (m_clock.getElapsedTime().asSeconds() > TIME_GAP_ESCALATOR) {
        m_dir = opposite(m_dir);
        m_clock.restart();
    }
    m_prevLoc = m_sprite.getPosition(); 
    m_sprite.move(toVector(m_dir) * MOVE_SPEED_ESCALATOR * delta.asSeconds());
}

sf::Vector2f Escalator::getPrevLoc() const
{
    return m_prevLoc;
}

void Escalator::goBack()
{
    m_sprite.setPosition(m_prevLoc);
}

bool Escalator::m_registerit =
Factory<StaticObject>::registerit
(
    std::string(1, Symbol::escalator), []()->std::unique_ptr<StaticObject>
    { return std::make_unique<Escalator>(); }
);