#pragma once
#include "StaticObject.h"
#include "Direction.h"
class Board;

const float TIME_GAP_ESCALATOR = 5.f; //for changing direction
const float MOVE_SPEED_ESCALATOR = 50.f;

class Escalator : public StaticObject {
public:
	Escalator();
	void update(sf::Time delta, Board& board) override;
	sf::Vector2f getPrevLoc() const;
	void goBack();
	
private:
	static bool m_registerit;
	sf::Clock m_clock; //for changing direction
	Direction m_dir = Direction::Up;
	sf::Vector2f m_prevLoc = m_sprite.getPosition();
};