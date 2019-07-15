#include <Application.hpp>
#include <Utility.hpp>
#include <State.hpp>
#include <StateIdentifiers.hpp>
#include <TitleState.hpp>
#include <GameState.hpp>
#include <MenuState.hpp>
#include <PauseState.hpp>
#include <ScoresState.hpp>
#include <GameOverState.hpp>


const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

// On initialise les ResourceHolders pour les textures/son/polices et on initialise le StateStack
Application::Application()
: mWindow(sf::VideoMode(1024, 768), "Audio", sf::Style::Close)
, mTextures()
, mFonts()
, mPlayer()
, mMusic()
, mSounds()
, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer, mMusic, mSounds))
, mStatisticsText()
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)
{
	mWindow.setKeyRepeatEnabled(false);
	mWindow.setVerticalSyncEnabled(true);

	mFonts.load(Fonts::Main, 	"Media/Sansation.ttf");

	mTextures.load(Textures::TitleScreen,	"Media/Textures/TitleScreen.png");
	mTextures.load(Textures::Buttons,		"Media/Textures/Buttons.png");

	mStatisticsText.setFont(mFonts.get(Fonts::Main));
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10u);

	registerStates();
	mStateStack.pushState(States::Title);

	mMusic.setVolume(25.f);
}

void Application::run()
{
	// Pour g�rer les �v�nements ind�pendemment du framerate
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);

			// Lorsqu'on quitte le dernier �tat (= on ferme le jeu)
			if (mStateStack.isEmpty())
				mWindow.close();
		}

		//updateStatistics(dt);
		render();
	}
}

// Gestion de l'input directement envoy�e au StateStack car �a d�pend de l'�tat du jeu
// eg. si on est dans le menu on ne g�re pas les touches de d�placement du joueur
void Application::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

// M�me chose que pour processInput()
void Application::update(sf::Time dt)
{
	mStateStack.update(dt);
}

void Application::render()
{
	mWindow.clear();

	mStateStack.draw();

	mWindow.setView(mWindow.getDefaultView());
	//mWindow.draw(mStatisticsText);

	mWindow.display();
}

void Application::updateStatistics(sf::Time dt)
{
	mStatisticsUpdateTime += dt;
	mStatisticsNumFrames += 1;
	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString("FPS: " + toString(mStatisticsNumFrames));

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Application::registerStates()
{
	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<PauseState>(States::Pause);
	mStateStack.registerState<ScoresState>(States::Scores);
	mStateStack.registerState<GameOverState>(States::GameOver);
}
