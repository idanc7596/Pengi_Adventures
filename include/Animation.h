#pragma once
#include "Direction.h"
#include "AnimationData.h"
#include "ResourcesManager.h"
#include <SFML/Graphics.hpp>


class Animation
{
public:
    Animation(const AnimationData& data, Direction dir, sf::Sprite& sprite, Texture id);
    void setDirection(Direction dir);
    void update(sf::Time delta);
    bool end() const;
    void reset();

private:
    void update();

    const AnimationData& m_data; //direction-->vector of intRects
    sf::Time m_elapsed = {};
    Direction m_dir = Direction::Right;
    int m_index = 0;
    int m_frame = 0; 
    sf::Sprite& m_sprite;
};
