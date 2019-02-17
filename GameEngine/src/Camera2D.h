#pragma once
#include"glm.hpp"
#include"gtc/matrix_transform.hpp"

namespace GameEngine
{
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();
		void init(int screenWidth, int screenHeight);
		void update();


		void setPosition(const glm::vec2& newPosition)
		{
			position = newPosition;
			needsMatrixUpdate = true;
		}
		void setScale(float newScale)
		{
			scale = newScale;
			needsMatrixUpdate = true;
		}

		glm::vec2 getPosition()
		{
			return position;
		}
		float getScale()
		{
			return scale;
		}
		glm::mat4 getcameraMatrix()
		{
			return cameraMatrix;
		}

	private:
		int _screenWidth, _screenHeight;
		bool needsMatrixUpdate;
		float scale;
		glm::vec2 position;
		glm::mat4 cameraMatrix;
		glm::mat4 orthoMatrix;

	};

}