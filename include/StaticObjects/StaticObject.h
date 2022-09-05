#pragma once
#include "GameObject.h"
class Board;

class StaticObject : public GameObject
{
public:
	StaticObject(Tiles id);
	virtual ~StaticObject() = default;
	virtual void update(sf::Time /*delta*/, Board& /*board*/) {};
	
private:
	
};
