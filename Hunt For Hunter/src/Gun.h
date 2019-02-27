#pragma once
#include <string>
#include<glm.hpp>
#include<vector>
#include "Bullets.h"

class Gun
{
public:
	Gun(std::string name,int fireRate,int bulletsPerShot,float spread ,float bulletDamage,float bulletSpeed);
	~Gun();

	void update(bool isMouseDown,const glm::vec2& position,const glm::vec2& direction, std::vector<Bullets>& bullets);

private:

	void fire(const glm::vec2& direction, const glm::vec2& position ,std::vector<Bullets>& bullets);

	std::string _name;
	int _fireRate;

	float _spread;

	int _bulletsPerShot;

	float _bulletSpeed;

	int _bulletDamage;

	int _frameCounter;

};

