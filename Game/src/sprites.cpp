#include "sprites.h"
#include "Common.h"


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

	float vertexData[12];
	vertexData[0] = x + width;
	vertexData[1] = y + height;
	vertexData[2] = x;
	vertexData[3] = y + height;
	vertexData[4] = x;
	vertexData[5] = y;

	vertexData[6] =x;
	vertexData[7] = y ;
	vertexData[8] = x+width;
	vertexData[9] = y ;
	vertexData[10] = x + width;
	vertexData[11] = y + height;

	GLError(glBindBuffer(GL_ARRAY_BUFFER, _vboID));
	GLError(glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW));

	GLError(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
void sprites::draw()
{
	GLError(glBindBuffer(GL_ARRAY_BUFFER, _vboID));
	GLError(glEnableVertexAttribArray(0));
	GLError(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0));
	GLError(glDrawArrays(GL_TRIANGLES, 0, 6));
	GLError(glDisableVertexAttribArray(0));
	GLError(glBindBuffer(GL_ARRAY_BUFFER, 0));

}