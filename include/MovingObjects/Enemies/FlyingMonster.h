#pragma once
#include "Enemy.h"

const float TIME_GAP_MONSTER = 5.f; //for changing direction

class FlyingMonster : public Enemy
{
public:
	FlyingMonster();
	void update(sf::Time delta, Board& /*board*/) override;

private:
	static bool m_registerit;
	sf::Clock m_clock; //for changing direction
};