#pragma once
#include "StaticObject.h"

class Bullet : public StaticObject {
public:
	Bullet(sf::Vector2f position);
	void update(sf::Time delta, Board& board) override;

private:
	float m_distancePassed = 0.f;

	const float moveSpeed = 100.f;
	const float maxDistance = 0.25 * WINDOW_WIDTH;
};