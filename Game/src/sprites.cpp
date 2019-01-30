#include "sprites.h"
#include "Common.h"
#include <cstddef>
#include "Vertex.h"
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

void sprites:: init(float x, float y, float width, float height)
{
	_x = x;
	_y = y;
	_height = height;
	_width = width;

	if (_vboID == 0)
	{
		GLError(glGenBuffers(1, &_vboID));
	}

	Vertex vertexData[12];
	vertexData[0].position.x = x + width;
	vertexData[0].position.y = y + height;
	vertexData[1].position.x = x;
	vertexData[1].position.y = y + height;
	vertexData[2].position.x = x;
	vertexData[2].position.y = y;

	vertexData[3].position.x =x;
	vertexData[3].position.y = y ;
	vertexData[4].position.x = x+width;
	vertexData[4].position.y = y ;
	vertexData[5].position.x = x + width;
	vertexData[5].position.y = y + height;

	
	
	vertexData[0].color.r = 0;
	vertexData[0].color.g = 0;
	vertexData[0].color.b = 0;
	vertexData[0].color.a = 0;
	
	vertexData[1].color.r = 0;
	vertexData[1].color.g = 255;
	vertexData[1].color.b = 0;
	vertexData[1].color.a = 0;

	vertexData[2].color.r = 255;
	vertexData[2].color.g = 0;
	vertexData[2].color.b = 0;
	vertexData[2].color.a = 0;

	vertexData[3].color.r = 0;
	vertexData[3].color.g = 0;
	vertexData[3].color.b = 255;
	vertexData[3].color.a = 0;

	vertexData[4].color.r = 0;
	vertexData[4].color.g = 0;
	vertexData[4].color.b = 0;
	vertexData[4].color.a = 255;

	vertexData[5].color.r = 255;
	vertexData[5].color.g = 255;
	vertexData[5].color.b = 255;
	vertexData[5].color.a = 255;
	

	GLError(glBindBuffer(GL_ARRAY_BUFFER, _vboID));
	GLError(glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW));

	GLError(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
void sprites::draw()
{
	GLError(glBindBuffer(GL_ARRAY_BUFFER, _vboID));
	GLError(glEnableVertexAttribArray(0));
	GLError(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*) offsetof(Vertex,position)));
	GLError(glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color)));
	GLError(glDrawArrays(GL_TRIANGLES, 0, 6));
	GLError(glDisableVertexAttribArray(0));
	GLError(glBindBuffer(GL_ARRAY_BUFFER, 0));

}