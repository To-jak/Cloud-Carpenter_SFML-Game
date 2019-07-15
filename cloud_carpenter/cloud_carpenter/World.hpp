#ifndef BOOK_WORLD_HPP
#define BOOK_WORLD_HPP

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <SceneNode.hpp>
#include <SpriteNode.hpp>
#include <SkyObject.hpp>
#include <CommandQueue.hpp>
#include <Command.hpp>
#include <SoundPlayer.hpp>
#include <ScrollingBackground.hpp>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>
#include <queue>


// Forward declaration
namespace sf
{
	class RenderTarget;
}

class World : private sf::NonCopyable
{
	public:
											World(sf::RenderTarget& outputTarget, FontHolder& fonts, SoundPlayer& sounds);
		void								update(sf::Time dt);
		void								draw();
		
		CommandQueue&						getCommandQueue();

		bool 								hasAlivePlayer() const;
		bool 								hasPlayerReachedEnd() const;
		int									getScore() const;

	private:
		void								loadTextures();
		void								adaptPlayerPosition();
		void								adaptPlayerVelocity();
		void								handleCollisions();
		void								updateSounds();

		void								buildScene();
		void								spawnEnemies(sf::Time dt);
		void								destroyEntitiesOutsideView();
		void								guideMissiles();
		sf::FloatRect						getViewBounds() const;
		sf::FloatRect						getBattlefieldBounds() const;


	private:
		enum Layer
		{
			Background,
			LowerAir,
			UpperAir,
			GUI,
			LayerCount
		};

		struct SpawnPoint 
		{
			SpawnPoint(SkyObject::Type type, float x, float y)
			: type(type)
			, x(x)
			, y(y)
			{
			}

			SkyObject::Type type;
			float x;
			float y;
		};


	private:
		sf::RenderTarget&					mTarget;
		sf::View							mWorldView;
		TextureHolder						mTextures;
		FontHolder&							mFonts;
		SoundPlayer&						mSounds;

		SceneNode							mSceneGraph;
		std::array<SceneNode*, LayerCount>	mSceneLayers;
		CommandQueue						mCommandQueue;

		sf::FloatRect						mWorldBounds;
		sf::Vector2f						mSpawnPosition;
		sf::Time							mEnemySpawnInterval;
		sf::Time							mEnemySpawnCountdown;
		float								mScrollSpeed;
		SkyObject*							mPlayerSkyObject;

		std::vector<SpawnPoint>				mEnemySpawnPoints;
		std::vector<SkyObject*>				mActiveEnemies;

		float								mScorePerSecond;
		float								mScore;

		TextNode*							mScoreDisplay;
		TextNode*							mMissileDisplay;
};

#endif // BOOK_WORLD_HPP
