#pragma once
#include "GameObject.h"
#include "Direction.h"
#include "Animation.h"
class Board;

class MovingObject : public GameObject
{
public:
	MovingObject(Objects object, Direction direction, Texture texture);
	virtual ~MovingObject() = default;
	virtual void update(sf::Time delta, Board& board) = 0;
	Direction getDirection() const;
	virtual void setDirection(sf::Keyboard::Key key);
	virtual void setDirection(Direction dir);
	void goBack();
	void oppositeDirectionX();
	void oppositeDirectionY();
	sf::Vector2f getPrevLoc() const;
	sf::Vector2f getVelocity() const;
	void setVelocity(sf::Vector2f velocity);
	
protected:
	Direction m_dir = Direction::Stay;
	Animation m_animation;
	sf::Vector2f m_prevLoc = m_sprite.getPosition();

	float m_gravity = 9.8f;
	int m_groundHeight = WINDOW_HEIGHT;
	sf::Vector2f m_velocity = { 0, 0 };
	float m_moveSpeed = 0;
};