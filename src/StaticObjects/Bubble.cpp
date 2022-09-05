#include "StaticObjects/Bubble.h"

Bubble::Bubble()
	: StaticObject(Tiles::bubble)
{
}

void Bubble::update(sf::Time /*delta*/, Board& /*board*/)
{
}



bool Bubble::m_registerit =
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::bubble), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Bubble>(); }
);