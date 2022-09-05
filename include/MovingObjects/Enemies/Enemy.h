#pragma once
#include "MovingObjects/MovingObject.h"

class Enemy : public MovingObject {
public:
	Enemy(Objects object, Direction direction, Texture texture);
	virtual ~Enemy() = default;

private:
	
};