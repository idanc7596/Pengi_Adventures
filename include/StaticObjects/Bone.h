#pragma once
#include "StaticObject.h"
#include "Animation.h"
class Player;
class Board;

class Bone : public StaticObject {
public:
	Bone(sf::Vector2f position, Player& player);
	void update(sf::Time delta, Board& board) override;


private:
	Animation m_animation;
	Player& m_player;
	Direction m_shootingDirection = Direction::Right;

	const float shootingSpeed = 300.f;
	const float shootingDistance = 0.4 * WINDOW_WIDTH;
};