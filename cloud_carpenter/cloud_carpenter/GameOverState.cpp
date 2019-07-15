#include <GameOverState.hpp>
#include <Utility.hpp>
#include <Player.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include <pugixml.hpp>


GameOverState::GameOverState(StateStack& stack, Context context)
: State(stack, context)
, mGameOverText()
, mElapsedTime(sf::Time::Zero)
{
	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	mGameOverText.setFont(font);
	if (context.player->getMissionStatus() == Player::MissionFailure)
		mGameOverText.setString("Mission failed!");	
	else
		mGameOverText.setString("Mission successful!");

	mGameOverText.setCharacterSize(70);
	centerOrigin(mGameOverText);
	mGameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

	// Sauvegarde du score

	std::shared_ptr<pugi::xml_document> doc = std::make_shared<pugi::xml_document>();

	pugi::xml_parse_result result = doc->load_file("Data/scores.xml",
		pugi::parse_default | pugi::parse_declaration);
	if (!result)
	{
		auto root = doc->append_child("root");

		bool saveSucceeded = doc->save_file("Data/scores.xml", "  ");
		assert(saveSucceeded);
	}

	pugi::xml_node root = doc->document_element();
	pugi::xml_node scoresNode;

	pugi::xpath_node search = root.select_single_node("Scores");
	if (!search)
	{
		// création de la sauvegarde
		scoresNode = root.append_child("Scores");
	}
	else {
		scoresNode = search.node();
	}
	pugi::xml_node nodeChild = scoresNode.append_child("PlayerName");
	nodeChild.append_child(pugi::node_pcdata).set_value(std::to_string(context.player->getScore()).c_str());

	bool saveSucceeded = doc->save_file("Data/scores.xml", "  ");
	assert(saveSucceeded);
}

void GameOverState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	// Create dark, semitransparent background
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mGameOverText);
}

bool GameOverState::update(sf::Time dt)
{
	// Show state for 3 seconds, after return to menu
	mElapsedTime += dt;
	if (mElapsedTime > sf::seconds(3))
	{
		requestStateClear();
		requestStackPush(States::Menu);
	}
	return false;
}

bool GameOverState::handleEvent(const sf::Event&)
{
	return false;
}
