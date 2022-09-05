#include "MovingObjects/Enemies/Jellyfish.h"
#include "Board.h"
#include "StaticObjects/Water.h"

Jellyfish::Jellyfish()
    :Enemy(Objects::jellyfish, Direction::Left, Texture::enemies)
{
    m_moveSpeed = 50.f;
    m_velocity.y = m_moveSpeed;
    m_sprite.setColor(sf::Color(255, 255, 255, 180)); //opacity
}

void Jellyfish::update(sf::Time delta, Board& board)
{
    //create water tile in the jellyfish position:
    if (firstTime) {
        auto waterTile = std::make_unique<Water>(Tiles::waterBottom);
        waterTile->setPosition(m_sprite.getPosition());
        board.addStaticObject(std::move(waterTile));
        firstTime = false;
    }

    if (m_clock.getElapsedTime().asSeconds() > timeGap) {
        oppositeDirectionY();
        m_clock.restart();
    }

    m_animation.update(delta);
    m_prevLoc = m_sprite.getPosition();
    m_sprite.move(m_velocity * delta.asSeconds());
}


bool Jellyfish::m_registerit =
Factory<MovingObject>::registerit
(
    std::string(1, Symbol::jellyfish), []()->std::unique_ptr<MovingObject>
    { return std::make_unique<Jellyfish>(); }
);
