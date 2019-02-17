#pragma once

#include "glm.hpp"
#include "SpriteBatch.h"

//equivalent class of bullet


class fireWeapon
{
public:
	fireWeapon(glm::vec2 pos, glm::vec2 dir, float speed, int lives);
	~fireWeapon();

	void draw(GameEngine::SpriteBatch& weaponSpriteBatch);
	bool updatePos();
private:
	int lifeTime;
	float fireSpeed;
	glm::vec2 direction;
	glm::vec2 position;
};

//glm::normalize