#include "StaticObjects/SpringBoard.h"
#include "ResourcesManager.h"
#include "Direction.h"

SpringBoard::SpringBoard()
	: m_animation(ResourcesManager::instance().getAnimationData(Objects::springBoard),
		Direction::Stay, m_sprite, Texture::tileSet),
		StaticObject(Tiles::springBoard)
{
}

void SpringBoard::update(sf::Time delta, Board& /*board*/)
{
	//the player stepped on springboard and the animation didn't end:
	if (m_active && !animationEnd()) {
		m_animation.update(sf::Time(sf::seconds(4*delta.asSeconds())));
	}
	else {
		reset(); //return the springboard to the initial mode
	}
}

void SpringBoard::setActive(bool active) {
	m_active = active;
}

bool SpringBoard::animationEnd() const
{
	//checks if the animation ends:
	return m_animation.end();
}

void SpringBoard::reset()
{
	//set springboard to the initial mode:
	m_active = false;
	m_animation.reset();
}

bool SpringBoard::m_registerit =
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::springBoard), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<SpringBoard>(); }
);
