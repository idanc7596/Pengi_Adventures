#include "GameObject.h"
#include "MovingObjects/MovingObject.h"


GameObject::GameObject()
{
}

void GameObject::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

sf::Vector2f GameObject::getPosition() const
{
	return m_sprite.getPosition();
}

void GameObject::setPosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
}

void GameObject::setOrigin(sf::Vector2f origin)
{
	m_sprite.setOrigin(origin);
}

sf::FloatRect GameObject::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

//checks if two objects intersect:
bool GameObject::collides(const GameObject& other) const
{
	if (&other == this) {
		return false;
	}
	return m_sprite.getGlobalBounds().intersects(other.m_sprite.getGlobalBounds());
}

bool GameObject::dispose() const
{
	return m_disposed;
}

void GameObject::setDispose()
{
	m_disposed = true;
}


