#include "sprites.h"
#include "Common.h"
#include <cstddef>
#include "Vertex.h"
#include "ResourceManager.h"

namespace GameEngine
{
	sprites::sprites()
	{
		_vboID = 0;
	}


	sprites::~sprites()
	{
		if (_vboID != 0)
		{
			GLError(glDeleteBuffers(1, &_vboID));
		}
	}

	void sprites::init(float x, float y, float width, float height, std::string texturePath)
	{
		_x = x;
		_y = y;
		_height = height;
		_width = width;

		_texture = ResourceManager::getTexture(texturePath);

		if (_vboID == 0)
		{
			GLError(glGenBuffers(1, &_vboID));
		}

		Vertex vertexData[12];

		vertexData[0].setPosition(x + width, y + height);
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPosition(x, y + height);
		vertexData[1].setUV(0.0f, 1.0f);

		vertexData[2].setPosition(x, y);
		vertexData[2].setUV(0.0f, 0.0f);

		vertexData[3].setPosition(x, y);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPosition(x + width, y);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5].setPosition(x + width, y + height);
		vertexData[5].setUV(1.0f, 1.0f);






		/*vertexData[0].setColor(0, 0, 0, 0);

		vertexData[1].setColor(0, 255, 0, 0);


		vertexData[2].setColor(255, 0, 0, 0);

		vertexData[3].setColor(0, 0, 255, 0);

		vertexData[4].setColor(0, 0, 0, 255);

		vertexData[5].setColor(255, 255, 255, 255);*/





		GLError(glBindBuffer(GL_ARRAY_BUFFER, _vboID));
		GLError(glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW));

		GLError(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
	void sprites::draw()
	{
		glBindTexture(GL_TEXTURE_2D, _texture.id);
		GLError(glBindBuffer(GL_ARRAY_BUFFER, _vboID));
		GLError(glEnableVertexAttribArray(0));
		GLError(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)));
		GLError(glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color)));
		GLError(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv)));
		GLError(glDrawArrays(GL_TRIANGLES, 0, 6));
		GLError(glDisableVertexAttribArray(0));
		GLError(glBindBuffer(GL_ARRAY_BUFFER, 0));

	}

}