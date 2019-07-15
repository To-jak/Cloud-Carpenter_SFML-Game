#include <ScrollingBackground.hpp>
#include <Foreach.hpp>
#include <iostream>

#include <SFML/Graphics/Sprite.hpp>
using namespace std;

ScrollingBackground::ScrollingBackground(sf::Texture& texture, sf::FloatRect worldBounds, int backgroundLength, float scrollSpeed) {

	sf::Sprite sprite(texture);
	sf::IntRect textureRect(sprite.getGlobalBounds());
	int textureLength = textureRect.height;

	for (int i = 0; i < backgroundLength; i++) {
		std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
		backgroundSprite->setPosition(0, 0 - i*textureLength);
		backgroundSprite->setVelocity(0, scrollSpeed*2);
		this->attachChild(std::move(backgroundSprite));
	}
	
	// nul mais j'ai pas encore trouvé d'autre moyen
	float mOffset = 50.f;
	mLimitPosition = worldBounds.height;
	mStartPosition = -backgroundLength * textureLength + worldBounds.height + mOffset;
}

void ScrollingBackground::updateChildren(sf::Time dt, CommandQueue & commands)
{
	FOREACH(Ptr& child, mChildren) {
		if (child->getPosition().y > mLimitPosition) {
			child->setPosition(child->getPosition().x, mStartPosition);
		}
		child->update(dt, commands);
	}
}