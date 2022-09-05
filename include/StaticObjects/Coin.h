#pragma once
#include "StaticObject.h"
#include "Animation.h"

class Coin : public StaticObject {
public:
	Coin();
	void update(sf::Time delta, Board& board) override;

private:
	Animation m_animation;

	static bool m_registerit;
};