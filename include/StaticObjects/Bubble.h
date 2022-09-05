#pragma once
#include "StaticObject.h"

class Bubble : public StaticObject {
public:
	Bubble();
	void update(sf::Time delta, Board& board) override;

private:

	static bool m_registerit;

};