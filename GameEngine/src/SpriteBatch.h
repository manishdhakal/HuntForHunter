#pragma once
#include"glew.h"
#include"Vertex.h"
#include"glm.hpp"
#include<vector>
namespace GameEngine
{
	
	struct Glyph {
		GLuint texture;
		float depth;

		Vertex TopLeft;
		Vertex BottomLeft;
		Vertex TopRight;
		Vertex BottomRight;
	};

	class RenderBatch
	{
	public:
		RenderBatch(GLuint Offset,GLuint Numvertices,GLuint texture):OffSet(Offset),
			NumVertices(Numvertices),
			Texture(texture) {}
		GLuint OffSet;
		GLuint NumVertices;
		GLuint Texture;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();
		void init();
		void begin();
		void  end();
		void draw(const glm::vec4& DestRect, const glm::vec4& UVRect, GLuint texture, float depth, const Color& color);
		void renderBatch();

	private:
		void CreateRenderBatches();
		void  CreateVertexArray();
		GLuint Vbo;
		GLuint Vao;
		std::vector<Glyph*>  Glyphs;
		std::vector<RenderBatch> RenderBatches;
	};
}