#include "Saviour.h"
#include"SDL.h"
//#include"Bullets.h"
#include"Gun.h"
Saviour::Saviour():
	_currentGunIndex(-1)
{
	spriteNum = 18;
}


Saviour::~Saviour()
{
}

void Saviour::init(float speed, glm::vec2 pos, GameEngine::keyHandler* keyHandler, GameEngine::Camera2D* camera, std::vector<Bullets>* bullets)
{
	_speed = speed;
	_position = pos;
	_keyHandler = keyHandler;
	_bullets = bullets;
	_camera = camera;
	_color.r = 242;
	_color.g = 147;
	_color.b = 106;
	_color.a = 255;


}

void Saviour::addGun(Gun* gun)
{
	_guns.push_back(gun);

	if (_currentGunIndex == -1)
	{
		_currentGunIndex = 0;
	}

}

void Saviour::update(const std::vector<std::string>& levelData,
	std::vector<Animal*>& animals,
	std::vector <Poachers*>& poachers)
{
	if (_keyHandler->iskeyPressed(SDLK_w))
	{
		if (spriteNum < 0 || spriteNum >= 8)
			spriteNum = 0;
		spriteNum++;
		_position.y += _speed;
	}
	else if (_keyHandler->iskeyPressed(SDLK_s))
	{
		if (spriteNum < 20 || spriteNum >= 28)
			spriteNum = 20;
		spriteNum++;
		_position.y -= _speed;
	}
	if (_keyHandler->iskeyPressed(SDLK_a))
	{
		if (spriteNum < 10 || spriteNum >= 18)
			spriteNum = 10;
		spriteNum++;
		_position.x -= _speed;
	}
	else if (_keyHandler->iskeyPressed(SDLK_d))
	{
		if (spriteNum < 30 || spriteNum >= 38)
			spriteNum = 30;
		spriteNum++;
		_position.x += _speed;
	}

	spriteFile = std::to_string(spriteNum) + std::string(".png");

	if (_keyHandler->iskeyPressed(SDLK_1) && _guns.size() >= 0)
	{
		_currentGunIndex = 0;
	}

	if (_keyHandler->iskeyPressed(SDLK_2) && _guns.size() >= 1)
	{
		_currentGunIndex = 1;
	}

	if (_keyHandler->iskeyPressed(SDLK_3) && _guns.size() >= 2)
	{
		_currentGunIndex = 2;
	}

	if (_currentGunIndex != -1)
	{

		glm::vec2 mouseCoords = _keyHandler->getMouseCoordinates();
		mouseCoords = _camera->ScreenToWorldCoordinates(mouseCoords);

		glm::vec2 centerPosition = _position + glm::vec2(AGENT_RADIUS);

		glm::vec2 direction= glm::normalize(mouseCoords - centerPosition);



		_guns[_currentGunIndex]->update(_keyHandler->iskeyPressed(SDL_BUTTON_LEFT),
			centerPosition,
			direction,
			*_bullets);
	}


	CollideWithLevel(levelData);



}
