#pragma once
#include "Enemy.h"
class Board;


class RollingEnemy : public Enemy {
public:
	RollingEnemy();
	void update(sf::Time delta, Board& board) override;
	bool rolling() const;
	void setRolling();

private:
	bool m_rolling = false;
	sf::Clock m_moveClock;
	sf::Clock m_rollingClock;
	float m_changeDirectionTime = 2.5f; //for changing direction
	const float rollingTime = 7.f;

	static bool m_registerit;


};