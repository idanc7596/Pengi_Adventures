#include "StaticObjects/StaticObject.h"

StaticObject::StaticObject(Tiles id)
{
	m_sprite.setTexture(ResourcesManager::instance().getTexture(Texture::tileSet));
	m_sprite.setTextureRect(ResourcesManager::instance().getTileRect(id));
	m_sprite.setOrigin(0.f, m_sprite.getGlobalBounds().height); //origin in bottom-left
}

