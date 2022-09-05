#pragma once
#include "StaticObjects/StaticObject.h"

class Water : public StaticObject {
public:
	Water(Tiles id);

private:
	static bool m_registerit;

};
