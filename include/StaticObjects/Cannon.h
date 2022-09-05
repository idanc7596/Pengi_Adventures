#pragma once
#include "StaticObject.h"
#include "Bullet.h"
#include <vector>
#include <memory>
class Board;

class Cannon : public StaticObject {
public:
	Cannon();
	void update(sf::Time delta, Board& board) override;

private:
	void spawnBullet(Board& board);

	static bool m_registerit;

	sf::Clock m_clock; //for spawning bullets
	const float spawnTime = 5.f;
};