#include "StaticObjects/Coin.h"
#include "Direction.h"

Coin::Coin()
	:StaticObject(Tiles::heart), //dummy
	m_animation(ResourcesManager::instance().getAnimationData(Objects::coin),
		Direction::Stay, m_sprite, Texture::tileSet)
{
	m_sprite.scale({ 0.9f, 0.9f });
}

void Coin::update(sf::Time delta, Board& /*board*/)
{
	m_animation.update(delta);
}


bool Coin::m_registerit =
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::coin), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Coin>(); }
);
