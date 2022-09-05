#pragma once
#include "StaticObject.h"

class Spike : public StaticObject 
{
public:
	Spike();

private:
	static bool m_registerit;

};