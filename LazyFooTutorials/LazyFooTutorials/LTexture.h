#ifndef LTEXTURE_H
#define LTEXTIRE_H

#include "LOpenGL.h"
#include <stdio.h>

class LTexture
{
	public:
		LTexture();
		~LTexture();
		bool loadTextureFromPixels32(GLuint* pixels, GLuint width, GLuint height);
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