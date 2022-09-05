#include "StaticObjects/Tile.h"
#include "ResourcesManager.h"

Tile::Tile(Tiles id)
	:StaticObject(id)
{
}

bool Tile::m_registerit =
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::grass), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::grass); }
)
&&
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::grassLeft), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::grassLeft); }
)
&&
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::grassRight), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::grassRight); }
)
&&
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::stones), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::stones); }
)
&&
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::stonesLeft), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::stonesLeft); }
)
&&
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::stonesRight), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::stonesRight); }
)
&&
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::soil), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::soil); }
)
&&
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::soilLeft), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::soilLeft); }
)
&&
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::soilRight), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::soilRight); }
)
&&
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::soilCornerLeft), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::soilCornerLeft); }
)
&&
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::soilCornerRight), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::soilCornerRight); }
)
&&
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::soilBottom), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::soilBottom); }
)
&&
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::soilHoles), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::soilHoles); }
)
&&
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::flatGrass), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::flatGrass); }
)
&&
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::flatGrassLeft), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::flatGrassLeft); }
)
&&
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::flatGrassRight), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::flatGrassRight); }
)
&&
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::wood), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::wood); }
)
&&
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::silverBrick), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::silverBrick); }
)
&&
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::goldBrick), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::goldBrick); }
)
&&
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::redBrick), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::redBrick); }
)
&&
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::woodBrick), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::woodBrick); }
)
&&
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::smallBrick), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::smallBrick); }
)
&&
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::largeBrick), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<Tile>(Tiles::largeBrick); }
);

