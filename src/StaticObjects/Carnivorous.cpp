#include "StaticObjects\Carnivorous.h"

Carnivorous::Carnivorous()
	:StaticObject(Tiles::carnivorous)
{
}

void Carnivorous::update(sf::Time delta, Board& /*board*/)
{
    //change direction every certain time:
    if (m_clock.getElapsedTime().asSeconds() > TIME_GAP_CARNIVOROUS) {
        m_dir = opposite(m_dir);
        m_clock.restart();
    }
    m_sprite.move(toVector(m_dir) * MOVE_SPEED_CARNIVOROUS * delta.asSeconds());
}

bool Carnivorous::m_registerit =
Factory<StaticObject>::registerit
(
    std::string(1, Symbol::carnivorous), []()->std::unique_ptr<StaticObject>
    { return std::make_unique<Carnivorous>(); }
);
