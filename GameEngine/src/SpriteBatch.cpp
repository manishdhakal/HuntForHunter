#include "SpriteBatch.h"
#include<algorithm>
#include"Common.h"
namespace GameEngine
{
	SpriteBatch::SpriteBatch():Vbo(0),Vao(0)
	{
	}


	SpriteBatch::~SpriteBatch()
	{
	}


	void SpriteBatch::init()
	{
		CreateVertexArray();
		
	}
	void SpriteBatch:: begin()
	{
		
		RenderBatches.clear();
		for (int i = 0; i < Glyphs.size(); i++)
		{
			delete Glyphs[i];
		}
		Glyphs.clear();
	}
	void SpriteBatch::end()
	{
		CreateRenderBatches();
	}
	// Every time the draw is called, a new glyph(sprite) is added to the vector of it

	void SpriteBatch::draw(const glm::vec4& DestRect, const glm::vec4& UVRect, GLuint texture, float depth, const Color& color)
	{
		Glyph* newGlyph= new Glyph;
		newGlyph->texture = texture;
		newGlyph->depth = depth;

		newGlyph->TopLeft.color = color;
		newGlyph->TopLeft.setPosition( DestRect.x,DestRect.y+DestRect.w);
		newGlyph->TopLeft.setUV(UVRect.x, UVRect.y + UVRect.w);

		newGlyph->BottomLeft.color = color;
		newGlyph->BottomLeft.setPosition(DestRect.x, DestRect.y );
		newGlyph->BottomLeft.setUV(UVRect.x, UVRect.y );

		newGlyph->BottomRight.color = color;
		newGlyph->BottomRight.setPosition(DestRect.x+ DestRect.z, DestRect.y);
		newGlyph->BottomRight.setUV(UVRect.x+UVRect.z, UVRect.y );

		newGlyph->TopRight.color = color;
		newGlyph->TopRight.setPosition(DestRect.x+DestRect.z, DestRect.y + DestRect.w);
		newGlyph->TopRight.setUV(UVRect.x+UVRect.z, UVRect.y + UVRect.w);

		Glyphs.push_back(newGlyph);
	}
	void SpriteBatch::renderBatch()
	{
		GLError(glBindVertexArray(Vao));
		for (int i = 0; i < RenderBatches.size(); i++)
		{
			GLError(glBindTexture(GL_TEXTURE_2D, RenderBatches[i].Texture));
			GLError(glDrawArrays(GL_TRIANGLES, RenderBatches[i].OffSet, RenderBatches[i].NumVertices));
		}

		GLError(glBindVertexArray(0));
	}

	void SpriteBatch::CreateRenderBatches()
	{
		std::vector <Vertex> Vertices;
		Vertices.resize(Glyphs.size() * 6);
		if (Glyphs.empty())
		{
			return;
		}
		int offset = 0;
		int CurrentVertex = 0;
		//RenderBatch MyBatch(0, 6, Glyphs[0]->texture);
		RenderBatches.emplace_back(0, 6, Glyphs[0]->texture);
		Vertices[CurrentVertex++] = Glyphs[0]->TopLeft;
		Vertices[CurrentVertex++] = Glyphs[0]->BottomLeft;
		Vertices[CurrentVertex++] = Glyphs[0]->BottomRight;
		Vertices[CurrentVertex++] = Glyphs[0]->BottomRight;
		Vertices[CurrentVertex++] = Glyphs[0]->TopRight;
		Vertices[CurrentVertex++] = Glyphs[0]->TopLeft;
		offset += 6;
		for (int cg = 1; cg < Glyphs.size() ;cg++)
		{
			if (Glyphs[cg]->texture != Glyphs[cg - 1]->texture)
			{
				RenderBatches.emplace_back(offset, 6, Glyphs[cg]->texture);

			}
			else
			{
				RenderBatches.back().NumVertices += 6;
			}
			//RenderBatches.emplace_back(0, 6, Glyphs[cg]->texture);
			Vertices[CurrentVertex++] = Glyphs[cg]->TopLeft;
			Vertices[CurrentVertex++] = Glyphs[cg]->BottomLeft;
			Vertices[CurrentVertex++] = Glyphs[cg]->BottomRight;
			Vertices[CurrentVertex++] = Glyphs[cg]->BottomRight;
			Vertices[CurrentVertex++] = Glyphs[cg]->TopRight;
			Vertices[CurrentVertex++] = Glyphs[cg]->TopLeft;

			offset += 6;

		}
		GLError(glBindBuffer(GL_ARRAY_BUFFER, Vbo));
		GLError(glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW));
		GLError(glBufferSubData(GL_ARRAY_BUFFER, 0, Vertices.size() * sizeof(Vertex), Vertices.data()));

		GLError(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void SpriteBatch::CreateVertexArray()
	{
		if (Vao == 0)
		{
			GLError(glGenVertexArrays(1, &Vao));
		}
		GLError(glBindVertexArray(Vao));
		if (Vbo == 0)
		{
			GLError(glGenBuffers(1, &Vbo));
		}
		GLError(glBindBuffer(GL_ARRAY_BUFFER, Vbo));

		GLError(glEnableVertexAttribArray(0));
		GLError(glEnableVertexAttribArray(1));
		GLError(glEnableVertexAttribArray(2));




		GLError(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)));
		GLError(glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color)));
		GLError(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv)));

		GLError(glBindVertexArray(0));


	}

	

}