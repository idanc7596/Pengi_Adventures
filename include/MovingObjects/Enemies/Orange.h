#pragma once
#include "Enemy.h"
class Board;

const float TIME_GAP_ORANGE = 5.f; //for changing direction

class Orange : public Enemy {
public:
	Orange();
	void update(sf::Time delta, Board& board) override;

private:
	static bool m_registerit;

	sf::Clock m_clock; //for changing direction
};