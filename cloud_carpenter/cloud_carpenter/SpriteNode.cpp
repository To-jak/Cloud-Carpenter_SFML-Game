#include <SpriteNode.hpp>

#include <SFML/Graphics/RenderTarget.hpp>


SpriteNode::SpriteNode(const sf::Texture& texture)
: Entity(1)
, mSprite(texture)
{

}	

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect)
: Entity(1)
, mSprite(texture, textureRect)
{
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}