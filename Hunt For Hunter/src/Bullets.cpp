#include "Bullets.h"
#include"ResourceManager.h"


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

void Bullets::update(std::vector<Animal*>& animals,
	std::vector <Poachers*>& poachers)
{
	_position += _direction * _speed;


}

void Bullets::draw(GameEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 destRect(_position.x + BULLET_RADIUS,
		_position.y + BULLET_RADIUS,
		BULLET_RADIUS*2,
		BULLET_RADIUS*2);
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	GameEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	spriteBatch.draw(destRect, uvRect, GameEngine::ResourceManager::getTexture("textures/bullet.png").id, 0.0f, color);
}
