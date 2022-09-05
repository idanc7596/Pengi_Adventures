#pragma once
#include "Enemy.h"
class Board;

class Jellyfish : public Enemy {
public:
	Jellyfish();
	void update(sf::Time delta, Board& board) override;

private:
	static bool m_registerit;

	//for changing direction:
	sf::Clock m_clock; 
	const float timeGap = 2.5f;
	bool firstTime = true;
};