#pragma once
#include <SFML/Graphics.hpp>
#include "macros.h"
#include "ResourcesManager.h"
#include "Factory.h"

class GameObject
{

public:
	GameObject();
	virtual ~GameObject() = default;
	virtual void draw(sf::RenderWindow& window) const;

	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f position);
	void setOrigin(sf::Vector2f origin);
	sf::FloatRect getGlobalBounds() const;
	bool collides(const GameObject& other) const;
	bool dispose() const;
	void setDispose();

protected:
	sf::Sprite m_sprite;
	bool m_disposed = false;
};