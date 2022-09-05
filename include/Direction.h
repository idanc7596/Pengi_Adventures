#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

enum class Direction
{
    Left,
    Right,
    Up,
    Down,
    Stay,
    SwimLeft,
    SwimRight,
    Max,
};

std::optional<Direction> toDirection(sf::Keyboard::Key key);
Direction opposite(Direction dir);
sf::Vector2f toVector(Direction dir);