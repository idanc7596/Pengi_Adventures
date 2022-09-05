#include "Animation.h"

const auto AnimationTime = sf::seconds(0.3f); //replace frame every AnimationTime

Animation::Animation(const AnimationData& data, Direction dir, sf::Sprite& sprite, Texture id)
    : m_data(data), m_dir(dir), m_sprite(sprite)
{
    m_sprite.setTexture(ResourcesManager::instance().getTexture(id));
    update();
    m_sprite.setOrigin(0.f, m_sprite.getGlobalBounds().height);
}

void Animation::setDirection(Direction dir)
{
    if (dir == Direction::Stay || dir == Direction::Up) 
    {
        return;
    }

    m_dir = dir;
}

void Animation::update(sf::Time delta)
{
    m_elapsed += delta;
    if (m_elapsed >= AnimationTime)
    {
        m_elapsed -= AnimationTime;
        //move to next frame:
        ++m_index; 
        ++m_frame;
        m_index %= m_data.m_data.find(m_dir)->second.size();
        update();
    }
}

bool Animation::end() const
{
    return m_frame >= m_data.m_data.find(m_dir)->second.size();
}

void Animation::reset()
{
    m_index = m_frame = 0;
    update();
}

void Animation::update()
{
    m_sprite.setTextureRect(m_data.m_data.find(m_dir)->second[m_index]);
    m_sprite.setOrigin(0.f, m_sprite.getGlobalBounds().height);
}
