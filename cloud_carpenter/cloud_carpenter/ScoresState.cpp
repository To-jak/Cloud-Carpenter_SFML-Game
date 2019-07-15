#include <ScoresState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <pugixml.hpp>
#include <iostream>

using namespace std;

ScoresState::ScoresState(StateStack& stack, Context context)
	: State(stack, context)
	, mTitle()
	, mScores()
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

	mTitle.setFont(context.fonts->get(Fonts::Main));
	mTitle.setString("TOP SCORES");
	centerOrigin(mTitle);
	mTitle.setPosition(sf::Vector2f(context.window->getSize().x / 2u, 100.f));

	mScores.setFont(context.fonts->get(Fonts::Main));

	auto backButton = std::make_shared<GUI::Button>(context);
	backButton->setPosition(80.f, 620.f);
	backButton->setText("Back");
	backButton->setCallback(std::bind(&ScoresState::requestStackPop, this));

	mGUIContainer.pack(backButton);

	getTopScores();
}

void ScoresState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);

	window.draw(mTitle);
	window.draw(mScores);

	window.draw(mGUIContainer);
}

bool ScoresState::update(sf::Time dt)
{
	return true;
}

bool ScoresState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return false;
}

void ScoresState::getTopScores()
{
	mScores.setString("");
	std::shared_ptr<pugi::xml_document> doc = std::make_shared<pugi::xml_document>();

	pugi::xml_parse_result result = doc->load_file("Data/scores.xml",
		pugi::parse_default | pugi::parse_declaration);
	if (!result)
	{
		mScores.setString("No top scores yet");
	}
	else {
		pugi::xml_node root = doc->document_element();
		pugi::xml_node scoresNode;

		pugi::xpath_node xpathNode = root.select_single_node("Scores");
		if (xpathNode)
		{
			scoresNode = xpathNode.node();
			std::vector<pair<std::string, int>> scores;
			for (pugi::xml_node child : scoresNode.children()) {
				scores.push_back(std::make_pair(child.name(), stoi(child.child_value())));
				std::sort(scores.begin(), scores.end(), [](auto &left, auto &right) {
					return left.second > right.second;
				});
			}
			for (int i = 0; i < min(5, static_cast<int>(scores.size())); i++) {
				mScores.setString(mScores.getString() + "\n" + std::to_string(i+1) + ". " + scores[i].first + " : " + std::to_string(scores[i].second));
			}
		}
		else {
			mScores.setString("No top scores yet");
		}
	}
	centerOrigin(mScores);
	mScores.setPosition(sf::Vector2f(512.f, 384.f));
}