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
Sprite * Objects::DuplicateSprite(Sprite * sprite)
{
	Sprite* pRet = Sprite::createWithTexture(sprite->getTexture());
	if (sprite->getChildrenCount() > 0)
	{
		for (int child = 0; child < sprite->getChildrenCount(); child++)
		{
			Sprite* spriteChild = (Sprite*)sprite->getChildren().at(child);
			Sprite* clone = DuplicateSprite((Sprite*)spriteChild);
			clone->boundingBox() = spriteChild->boundingBox();
			clone->setContentSize(spriteChild->getContentSize());
			clone->setPosition(spriteChild->getPosition());
			clone->setAnchorPoint(spriteChild->getAnchorPoint());
			pRet->addChild(clone, spriteChild->getZOrder(), spriteChild->getTag());
		}
	}
	return pRet;
}

