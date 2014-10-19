#ifndef LTEXTURE_H
#define LTEXTIRE_H

#include "LOpenGL.h"
#include <stdio.h>
#include <string>

class LTexture
{
	public:
		LTexture();
		~LTexture();
		bool loadTextureFromPixels32(GLuint* pixels, GLuint width, GLuint height);
		bool loadTextureFromFile(std::string path);
		void freeTexture();
		void render(GLfloat x, GLfloat y);
		GLuint getTextureID();
		GLuint textureWidth();
		GLuint textureHeight();
	private:
		GLuint mTextureID;

		GLuint mTextureWidth;
		GLuint mTextureHeight;
};

#endif