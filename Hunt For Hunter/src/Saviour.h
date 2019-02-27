#pragma once
#include"Animal.h"
#include"keyHandler.h"
#include"Camera2D.h"
#include"Bullets.h"


class Gun;

class Saviour:public Animal
{
public:
	Saviour();
	~Saviour();

	void init(float speed,glm::vec2 pos, GameEngine::keyHandler* keyHandler,GameEngine::Camera2D* camera , std::vector<Bullets>* bullets);

	void addGun(Gun* gun);

	void update(const std::vector<std::string>& levelData,
		std::vector<Animal*>& animals,
		std::vector <Poachers*>& poachers) override;
private:
	int spriteNum;
	GameEngine::keyHandler* _keyHandler;

	std::vector<Gun*> _guns;
	int _currentGunIndex;

	GameEngine::Camera2D* _camera;
	std::vector<Bullets>* _bullets;

};

