#include "StaticObjects/Spike.h"


Spike::Spike()
	:StaticObject(Tiles::spike)
{
}


bool Spike::m_registerit =
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::spike), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Spike>(); }
);
