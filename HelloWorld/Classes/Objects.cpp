#include "Objects.h"

Objects::Objects()
{
}

Objects::~Objects()
{
}

void Objects::setSprite(Sprite* sprite)
{
	this->m_Sprite = sprite;
}

Sprite * Objects::getSprite()
{
	return m_Sprite;
}
