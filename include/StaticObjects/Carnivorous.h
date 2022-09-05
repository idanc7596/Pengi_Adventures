#pragma once
#include "StaticObject.h"
#include "Direction.h"
class Board;

const float TIME_GAP_CARNIVOROUS = 3.f; 
const float MOVE_SPEED_CARNIVOROUS = 30.f;

class Carnivorous : public StaticObject {
public:
	Carnivorous();
	void update(sf::Time delta, Board& board) override;

private:
	static bool m_registerit;
	sf::Clock m_clock;
	Direction m_dir = Direction::Down;
};