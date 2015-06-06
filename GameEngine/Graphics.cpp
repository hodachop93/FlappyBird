#include "GameEngine.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define NUMBER_ARC_VERTICES 60
#define PI_TO_RAD (((float) M_PI) / 180.0f)

namespace gamerize
{

	struct Vertex
	{
		Vector2 position;
		Vector2 uv;
	};

	const char simpleVertexShader[] =
		"attribute vec2 aPosition;\n"
		"attribute vec2 aUV;\n"
		"varying vec2 vUV;\n"
		"uniform mat4 uTransformMatrix;\n"
		"void main() {\n"
		"	gl_Position = uTransformMatrix * vec4(aPosition, 0.0, 1.0);\n"
		"   vUV = vec2(aUV.x, aUV.y);\n"
		"}";

	const char simpleFragmentShader[] =
		"varying lowp vec2 vUV;\n"
		"uniform sampler2D uTexture;\n"
		"uniform highp vec4 uColor;\n"
		"uniform bool uHasTexture;\n"
		"void main() {\n"		
		"	if (uHasTexture) { \n"
		"		gl_FragColor = texture2D(uTexture, vUV);\n"
		"	} else { \n"
		"		gl_FragColor = uColor;\n"
		"	}\n"
		"}";
	// iNitialize the graphics device
	Graphics::Graphics(int width, int height)
	{
		this->width = width;
		this->height = height;

		shader.Init(simpleVertexShader, simpleFragmentShader);

		Matrix translate, scale;		
		scale.SetScale(2.0f / width, -2.0f / height, 1.0f);		
		translate.SetTranslation(-width / 2.0f, -height / 2.0f, 0.0f);
		transformMatrix = translate * scale;
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	// Destroy the graphics device
	Graphics::~Graphics()
	{
	}

	// Clear screen
	void Graphics::ClearScreen(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	// Set the color
	void Graphics::SetColor(float r, float g, float b, float a)
	{
		color = Vector4(r, g, b, a);
	}

	void Graphics::DrawRect(float x, float y, float w, float h)
	{
		Vector2 vertices[4] = {
			Vector2(x, y),
			Vector2(x + w, y),
			Vector2(x + w, y + h),
			Vector2(x, y + h)
		};

		DrawPrimitive(GL_LINE_LOOP, vertices, 0, 4);

	}

	void Graphics::FillRect(float x, float y, float w, float h)
	{
		Vector2 vertices[4] = {
			Vector2(x, y),
			Vector2(x + w, y),
			Vector2(x + w, y + h),
			Vector2(x, y + h)
		};

		DrawPrimitive(GL_TRIANGLE_FAN, vertices, 0, 4);
	}

	void Graphics::DrawArc(float x, float y, float r, float start, float end)
	{
		Vector2 vertices[NUMBER_ARC_VERTICES + 1];
		float step = (end - start) / (NUMBER_ARC_VERTICES - 1);
		float alpha = start;
		vertices[0] = Vector2(x, y);
	
		for (int i = 1; i <= NUMBER_ARC_VERTICES; i++)
		{			
			vertices[i] = Vector2(x + r * cos(alpha * PI_TO_RAD), y - r * sin(alpha * PI_TO_RAD)); 
			alpha += step;
		}

		DrawPrimitive(GL_LINE_LOOP, vertices, 0, NUMBER_ARC_VERTICES + 1);
	}

	void Graphics::FillArc(float x, float y, float r, float start, float end)
	{
		Vector2 vertices[NUMBER_ARC_VERTICES + 1];
		float step = (end - start) / (NUMBER_ARC_VERTICES - 1);
		float alpha = start;
		vertices[0] = Vector2(x, y);
	
		for (int i = 1; i <= NUMBER_ARC_VERTICES; i++)
		{			
			vertices[i] = Vector2(x + r * cos(alpha * PI_TO_RAD), y - r * sin(alpha * PI_TO_RAD)); 
			alpha += step;
		}

		DrawPrimitive(GL_TRIANGLE_FAN, vertices, 0, NUMBER_ARC_VERTICES + 1);
	}

	void Graphics::DrawLine(float x1, float y1, float x2, float y2)
	{
		Vector2 vertices[2] = {
			Vector2(x1, y1),
			Vector2(x2, y2)
		};

		DrawPrimitive(GL_LINES, vertices, 0, 2);
	}

	// Draw image 
	void Graphics::DrawImage(Image *image, float x, float y, int alignment)
	{
		if (alignment & HCENTER)
		{
			x -= image->GetWidth() >> 1;
		}
		else if (alignment & RIGHT)
		{
			x -= image->GetWidth();
		}

		if (alignment & VCENTER)
		{
			y -= image->GetHeight() >> 1;
		}
		else if (alignment & BOTTOM)
		{
			y -= image->GetHeight();
		}


		Vertex vertices[4] = {
			Vector2(x, y),
			image->GetTextureCoord(0.0f, 0.0f),
			Vector2(x + image->GetWidth(), y),
			image->GetTextureCoord((float) image->GetWidth(), 0.0f),
			Vector2(x + image->GetWidth(), y + image->GetHeight()),
			image->GetTextureCoord((float) image->GetWidth(), (float) image->GetHeight()),
			Vector2(x, y + image->GetHeight()),
			image->GetTextureCoord(0.0f, (float) image->GetHeight())
		};

		glUseProgram(shader.program);
		if (shader.positionAttribute != -1)
		{
			glEnableVertexAttribArray(shader.positionAttribute);
			glVertexAttribPointer(shader.positionAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), &vertices[0].position);
		}

		if (shader.uvAttribute != -1)
		{
			glEnableVertexAttribArray(shader.uvAttribute);
			glVertexAttribPointer(shader.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), &vertices[0].uv);
		}

		if (shader.colorUniform != -1)
		{
			glUniform4f(shader.colorUniform, color.x, color.y, color.z, color.w);
		}

		if (shader.hasTextureUniform != -1)
		{
			glUniform1i(shader.hasTextureUniform, 1);
		}

		if (shader.transformMatrixUniform != -1)
		{
			glUniformMatrix4fv(shader.transformMatrixUniform, 1, GL_FALSE, (float *) transformMatrix.m);
		}
		
		if (shader.textureUniform != -1)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, image->GetTextureId());
			glUniform1i(shader.textureUniform, 0);			
		}

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glBindTexture(GL_TEXTURE_2D, 0);
		
	}

	void Graphics::DrawPrimitive(unsigned int primitive, void *vertexData, int start, int count)
	{
		glUseProgram(shader.program);
		if (shader.positionAttribute != -1)
		{
			glEnableVertexAttribArray(shader.positionAttribute);
			glVertexAttribPointer(shader.positionAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), vertexData);
		}

		if (shader.colorUniform != -1)
		{
			glUniform4f(shader.colorUniform, color.x, color.y, color.z, color.w);
		}

		if (shader.hasTextureUniform != -1)
		{
			glUniform1i(shader.hasTextureUniform, 0);
		}

		if (shader.transformMatrixUniform != -1)
		{
			glUniformMatrix4fv(shader.transformMatrixUniform, 1, GL_FALSE, (float *) transformMatrix.m);
		}
		
		glDrawArrays(primitive, start, count);
	}
};