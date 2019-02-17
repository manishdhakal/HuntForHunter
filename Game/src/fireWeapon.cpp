#include "fireWeapon.h"
#include "ResourceManager.h"


fireWeapon::fireWeapon(glm::vec2 pos, glm::vec2 dir, float speed, int lives)
{
	fireSpeed = speed;
	position = pos;
	direction = dir;
	lifeTime = lives;

}


fireWeapon::~fireWeapon()
{
}

	
void fireWeapon::draw(GameEngine::SpriteBatch& weaponSpriteBatch){
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GameEngine::GLTexture texture = GameEngine::ResourceManager::getTexture("textures/fireball.png");
	GameEngine::Color  color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	glm::vec4 posAndSize = glm::vec4(position.x, position.y, 30, 30);
	weaponSpriteBatch.draw(posAndSize, uv, texture.id, 0.0f, color);
}

bool fireWeapon::updatePos() {
	position += direction * fireSpeed;
	lifeTime--;
	if (lifeTime == 0) {
		return true;
	}
	return false;
}
