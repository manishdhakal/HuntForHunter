#define GLM_ENABLE_EXPERIMENTAL

#include "Gun.h"
#include<random>
#include<ctime>

#include<gtx/rotate_vector.hpp>
Gun::Gun(std::string name, int fireRate, int bulletPerShot, float spread, float bulletDamage, float bulletSpeed):
	_name(name),
	_fireRate(fireRate),
	_bulletsPerShot(bulletPerShot),
	_spread(spread),
	_bulletSpeed(bulletSpeed),
	_bulletDamage(bulletDamage),
	_frameCounter(0)
{
}


Gun::~Gun()
{
}

void Gun::update(bool isMouseDown,const glm::vec2& position,const glm::vec2& direction, std::vector<Bullets>& bullets)
{
	_frameCounter++;
	if (_frameCounter >= _fireRate && isMouseDown)
	{
		fire(direction,position, bullets);
		_frameCounter = 0;
	}

}

void Gun::fire(const glm::vec2& direction, const glm::vec2& position, std::vector<Bullets>& bullets)
{

	static std::mt19937 randomEngine(time(nullptr));

	 std::uniform_real_distribution<float> randRotate(-_spread, _spread);

	for (int i = 0; i < _bulletsPerShot; i++)
	{
		bullets.emplace_back(position,
			glm::rotate(direction,randRotate(randomEngine)),
				_bulletDamage,
				_bulletSpeed);
	}
}