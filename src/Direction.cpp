#include "Direction.h"
#include <stdexcept>


std::optional<Direction> toDirection(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::Left:
        return Direction::Left;
    case sf::Keyboard::Right:
        return Direction::Right;
    case sf::Keyboard::Space:
        return Direction::Up;
    case sf::Keyboard::Up:
        return Direction::Up;
    default:
        return {};
    }
}

Direction opposite(Direction dir)
{
    switch (dir)
    {
    
    case Direction::Left:
        return Direction::Right;
    case Direction::Right:
        return Direction::Left;
    case Direction::Up:
        return Direction::Down;
    case Direction::Down:
        return Direction::Up;
    case Direction::Stay:
        return Direction::Stay;
    default:
        throw std::runtime_error("Unknown direction");
    }
}

sf::Vector2f toVector(Direction dir)
{
    switch (dir)
    {
    case Direction::Left:
        return { -1, 0 };
    case Direction::Right:
        return { 1, 0 };
    case Direction::Up:
        return { 0, -1 };
    case Direction::Down:
        return { 0, 1 };
    case Direction::Stay:
        return { 0, 0 };
    default:
        throw std::runtime_error("Unknown direction");
    }
}
