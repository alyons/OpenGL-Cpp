#pragma once

#include <string>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "RectangleF.h"

class Texture
{
public:
	Texture(); // Initialize Texture
	~Texture(); // Free Texture
	bool loadTextureFromPixel32(GLuint* pixels, GLuint imgWidth, GLuint imgHeight, GLuint texWidth, GLuint texHeight); // Load image from pixel data
	void freeTexture(); // Delete texture (if exists) and set id to 0
	void render(GLfloat x, GLfloat y, RectangleF* clip = NULL); // Render the image on the screen
	GLuint getTextureID(); // Return the texture ID
	GLuint textureWidth(); // Return the texture width
	GLuint textureHeight(); // Return the texture height
	bool loadTextureFromFile(std::string path);

private:
	GLuint powerOfTwo(GLuint num);
	GLuint mTextureID;
	GLuint mTextureWidth;
	GLuint mTextureHeight;
	GLuint mImageWidth;
	GLuint mImageHeight;
};

