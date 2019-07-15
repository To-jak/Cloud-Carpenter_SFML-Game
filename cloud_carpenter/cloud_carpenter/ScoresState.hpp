#pragma once
#include "State.hpp"
#include "Container.hpp"
#include "Button.hpp"
#include "Label.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class ScoresState : public State
{
public:
	ScoresState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);
	virtual void		getTopScores();

private:
	sf::Sprite			mBackgroundSprite;
	GUI::Container		mGUIContainer;
	sf::Text			mTitle;
	sf::Text			mScores;
};