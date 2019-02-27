#include "Bullets.h"



Bullets::Bullets(glm::vec2 position, glm::vec2 direction, float damage, float speed):
	_position(position),
	_direction(direction),
	_damage(damage),
	_speed(speed)

{
}


Bullets::~Bullets()
{
}
