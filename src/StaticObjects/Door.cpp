#include "StaticObjects/Door.h"

Door::Door(Tiles id)
	:StaticObject(id)
{
}


bool Door::m_registerit =
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::door), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Door>(Tiles::door); }
);