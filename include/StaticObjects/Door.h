#pragma once
#include "StaticObject.h"

class Door : public StaticObject {
public:
	Door(Tiles id);

private:
	static bool m_registerit;

};