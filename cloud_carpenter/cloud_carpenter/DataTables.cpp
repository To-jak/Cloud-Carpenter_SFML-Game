#include <DataTables.hpp>
#include <SkyObject.hpp>
#include <Projectile.hpp>
#include <Pickup.hpp>
#include <Particle.hpp>


// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

std::vector<SkyObjectData> initializeSkyObjectData()
{
	std::vector<SkyObjectData> data(SkyObject::TypeCount);

	data[SkyObject::Player].hitpoints = 100;
	data[SkyObject::Player].speed = 200.f;
	data[SkyObject::Player].fireInterval = sf::seconds(1);
	data[SkyObject::Player].texture = Textures::Entities;
	data[SkyObject::Player].textureRect = sf::IntRect(0, 0, 48, 64);
	data[SkyObject::Player].hasRollAnimation = true;

	data[SkyObject::Vulture].hitpoints = 20;
	data[SkyObject::Vulture].speed = 400.f;
	data[SkyObject::Vulture].texture = Textures::Entities;
	data[SkyObject::Vulture].textureRect = sf::IntRect(144, 0, 84, 64);
	data[SkyObject::Vulture].directions.push_back(Direction(+45.f, 180.f));
	data[SkyObject::Vulture].directions.push_back(Direction(-45.f, 360.f));
	data[SkyObject::Vulture].directions.push_back(Direction(+45.f, 180.f));
	data[SkyObject::Vulture].fireInterval = sf::Time::Zero;
	data[SkyObject::Vulture].hasRollAnimation = false;

	data[SkyObject::BadCloud].hitpoints = 40;
	data[SkyObject::BadCloud].speed = 500.f;
	data[SkyObject::BadCloud].texture = Textures::Entities;
	data[SkyObject::BadCloud].textureRect = sf::IntRect(228, 0, 60, 59);
	data[SkyObject::BadCloud].directions.push_back(Direction(+45.f,  50.f));
	data[SkyObject::BadCloud].directions.push_back(Direction(  0.f,  50.f));
	data[SkyObject::BadCloud].directions.push_back(Direction(-45.f, 100.f));
	data[SkyObject::BadCloud].directions.push_back(Direction(  0.f,  50.f));
	data[SkyObject::BadCloud].directions.push_back(Direction(+45.f,  50.f));
	data[SkyObject::BadCloud].fireInterval = sf::seconds(2);
	data[SkyObject::BadCloud].hasRollAnimation = false;

	return data;
}

std::vector<ProjectileData> initializeProjectileData()
{
	std::vector<ProjectileData> data(Projectile::TypeCount);

	data[Projectile::AlliedBullet].damage = 10;
	data[Projectile::AlliedBullet].speed = 300.f;
	data[Projectile::AlliedBullet].texture = Textures::Entities;
	data[Projectile::AlliedBullet].textureRect = sf::IntRect(175, 64, 3, 14);

	data[Projectile::EnemyBullet].damage = 10;
	data[Projectile::EnemyBullet].speed = 300.f;
	data[Projectile::EnemyBullet].texture = Textures::Entities;
	data[Projectile::EnemyBullet].textureRect = sf::IntRect(178, 64, 3, 14);

	data[Projectile::Missile].damage = 200;
	data[Projectile::Missile].speed = 150.f;
	data[Projectile::Missile].texture = Textures::Entities;
	data[Projectile::Missile].textureRect = sf::IntRect(160, 64, 15, 32);

	return data;
}

std::vector<PickupData> initializePickupData()
{
	std::vector<PickupData> data(Pickup::TypeCount);
	
	data[Pickup::HealthRefill].texture = Textures::Entities;
	data[Pickup::HealthRefill].textureRect = sf::IntRect(0, 64, 40, 40);
	data[Pickup::HealthRefill].action = [] (SkyObject& a) { a.repair(25); };
	
	data[Pickup::MissileRefill].texture = Textures::Entities;
	data[Pickup::MissileRefill].textureRect = sf::IntRect(40, 64, 40, 40);
	data[Pickup::MissileRefill].action = std::bind(&SkyObject::collectMissiles, _1, 3);
	
	data[Pickup::FireSpread].texture = Textures::Entities;
	data[Pickup::FireSpread].textureRect = sf::IntRect(80, 64, 40, 40);
	data[Pickup::FireSpread].action = std::bind(&SkyObject::increaseSpread, _1);
	
	data[Pickup::FireRate].texture = Textures::Entities;
	data[Pickup::FireRate].textureRect = sf::IntRect(120, 64, 40, 40);
	data[Pickup::FireRate].action = std::bind(&SkyObject::increaseFireRate, _1);

	return data;
}

std::vector<ParticleData> initializeParticleData()
{
	std::vector<ParticleData> data(Particle::ParticleCount);

	data[Particle::Propellant].color = sf::Color(255, 255, 50);
	data[Particle::Propellant].lifetime = sf::seconds(0.6f);

	data[Particle::Smoke].color = sf::Color(50, 50, 50);
	data[Particle::Smoke].lifetime = sf::seconds(4.f);

	return data;
}
