#include "Camera2D.h"

namespace GameEngine
{

	Camera2D::Camera2D() :position(0.0f, 0.0f),
		cameraMatrix(1.0f),
		orthoMatrix(1.0f),
		scale(1.0f),
		needsMatrixUpdate(true),
		_screenHeight(500),
		_screenWidth(500)
	{
	}


	Camera2D::~Camera2D()
	{
	}
	void Camera2D::init(int screenWidth, int screenHeight)
	{
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		orthoMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
	}
	void Camera2D::update()
	{
		if (needsMatrixUpdate)
		{
			glm::vec3 translate(-position.x+_screenWidth/2, -position.y+_screenHeight/2, 0.0f);
			cameraMatrix = glm::translate(orthoMatrix, translate);

			glm::vec3 scale(scale, scale, 0.0f);
			cameraMatrix = glm::scale(glm::mat4(1.0f), scale)*cameraMatrix;
			//translate = glm::vec3(screenWidth/2,screenHeight/2, 0.0f);
			//cameraMatrix = glm::translate(orthoMatrix, translate);
			needsMatrixUpdate = false;
		}
	}
	glm::vec2 Camera2D::ScreenToWorldCoordinates(glm::vec2 screenCoordinates) {\

		screenCoordinates.y = _screenHeight - screenCoordinates.y;

		screenCoordinates -= glm::vec2(_screenWidth / 2, _screenHeight / 2);

		screenCoordinates /= scale;

		screenCoordinates += position;

		return screenCoordinates;
	}


}