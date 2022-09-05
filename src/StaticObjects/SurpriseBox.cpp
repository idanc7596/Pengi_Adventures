#include "StaticObjects/SurpriseBox.h"
#include "StaticObjects/Coin.h"
#include "Board.h"

SurpriseBox::SurpriseBox()
	:Tile(Tiles::surpriseBox)
{
}

void SurpriseBox::update(sf::Time /*delta*/, Board& board)
{
	//the player heads the surprisebox, and it wasn't opened before:
	if (m_dropCoin && !m_opened) {
		ResourcesManager::instance().playSound(Sound::surpriseBox);
		spawnCoin(board);
		m_opened = true;
	}
}

void SurpriseBox::dropCoin()
{
	m_dropCoin = true;
}

void SurpriseBox::spawnCoin(Board& board)
{
	sf::Vector2f spawnPosition = {m_sprite.getPosition().x, m_sprite.getPosition().y - 50.f};
	auto coin = std::make_unique<Coin>();
	coin->setPosition(spawnPosition);
	board.addStaticObject(std::move(coin));
	m_dropCoin = false;
}

bool SurpriseBox::m_registerit =
Factory<StaticObject>::registerit
(
	std::string(1, Symbol::surpriseBox), []()->std::unique_ptr<StaticObject>
	{ return std::make_unique<SurpriseBox>(); }
);

