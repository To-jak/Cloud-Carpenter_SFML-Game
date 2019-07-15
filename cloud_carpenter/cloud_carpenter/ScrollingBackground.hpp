#pragma once

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SpriteNode.hpp"

class ScrollingBackground : public SceneNode
{
	public:
								ScrollingBackground(sf::Texture& texture, sf::FloatRect WorldBounds, int backgroundLength, float ScrollSpeed);

	private:
		void					updateChildren(sf::Time dt, CommandQueue& commands) override;

	private:
		float					mLimitPosition;
		float					mStartPosition;
};
