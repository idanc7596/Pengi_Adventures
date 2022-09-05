#pragma once
#include "StaticObjects/StaticObject.h"

class Tile : public StaticObject {
public:
	Tile(Tiles id);

private:
	static bool m_registerit;
	
};
