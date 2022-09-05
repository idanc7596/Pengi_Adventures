#pragma once
#include "StaticObject.h"
#include "Direction.h"
#include "Animation.h"
#include "MovingObjects/Player.h"

class SpringBoard : public StaticObject {
public:
	SpringBoard();
	void update(sf::Time delta, Board& board) override;
	void setActive(bool active);
	bool animationEnd() const;
	void reset();

private:
	static bool m_registerit;
	Animation m_animation;
	bool m_active = false; //player stepped on it
};