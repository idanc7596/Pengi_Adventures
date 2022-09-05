#pragma once
#include "Board.h"
#include "Tile.h"
#include <vector>
#include <memory>

class SurpriseBox : public Tile
{
public:
	SurpriseBox();
	void update(sf::Time delta, Board& board) override;
	void dropCoin();
	void spawnCoin(Board& board);

private:
	static bool m_registerit;
	bool m_dropCoin = false;
	bool m_opened = false;
};