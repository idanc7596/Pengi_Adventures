#pragma once
#include "MovingObject.h"
class Board;
class Bubble;

class Player : public MovingObject
{
public:
	Player();
	void canJump(bool jump);
	void update(sf::Time delta, Board& board);
	void move(sf::Time delta);
	void littleJump();
	void setDirection(sf::Keyboard::Key key) override;
	void setDirection(Direction dir) override;
	void shoot(Board& board);
	void setInWater(bool inWater);
	bool checkInWater(Board& board);
	bool isFaceLeft() const;

	int getScore() const;
	int getLives() const;
	void setLives(int lives);
	void decreaseLives();
	void addScore(int add);
	bool win() const;
	void setWin();
	bool defended() const;
	void setDefended(Bubble& bubble); 

	void resetForNewLevel();
	void resetForRestartLevel();

private:
	void handleDefence();

	const int numOfLives = 3;
	int m_score = 0;
	int m_lives = numOfLives;
	bool m_win = false;

	float m_jumpSpeed = 432.f;
	bool m_canJump = false;
	bool m_isJump = false;
	bool m_inWater = false;
	sf::Clock m_waterClock; //for bubbles sound
	const float waterTimeGap = 3.f;

	bool m_defended = false; //has defence bubble

	sf::Clock m_clock;
	bool m_faceLeft = false;
	const float shootTimeGap = 0.5f;

	sf::Clock m_defenceClock;
	const float defenceTime = 10.f;
	Bubble* m_bubble = nullptr; //defence bubble
};


	