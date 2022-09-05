#include "StaticObjects/Water.h"
#include "ResourcesManager.h"

Water::Water(Tiles id)
	:StaticObject(id)
{
}

bool Water::m_registerit =
Factory<StaticObject>::registerit
(
    std::string(1, Symbol::water), []()->std::unique_ptr<StaticObject>
    { return std::make_unique<Water>(Tiles::water); }
)
&&
Factory<StaticObject>::registerit
(
    std::string(1, Symbol::waterBottom), []()->std::unique_ptr<StaticObject>
    { return std::make_unique<Water>(Tiles::waterBottom); }
)
&&
Factory<StaticObject>::registerit
(
    std::string(1, Symbol::waterCornerLeft), []()->std::unique_ptr<StaticObject>
    { return std::make_unique<Water>(Tiles::waterCornerLeft); }
)
&&
Factory<StaticObject>::registerit
(
    std::string(1, Symbol::waterCornerRight), []()->std::unique_ptr<StaticObject>
    { return std::make_unique<Water>(Tiles::waterCornerRight); }
);



