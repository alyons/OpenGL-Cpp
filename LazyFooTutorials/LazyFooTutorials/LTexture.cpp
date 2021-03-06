#include "LTexture.h"
#include <il/il.h>
#include <il/ilu.h>

LTexture::LTexture()
{
	mTextureID = 0;

	mTextureWidth = 0;
	mTextureHeight = 0;
}

LTexture::~LTexture()
{
	freeTexture();
}

bool LTexture::loadTextureFromPixels32(GLuint* pixels, GLuint width, GLuint height)
{
	// Clear old data
	freeTexture();

	// Assign the texture size
	mTextureWidth = width;
	mTextureHeight = height;

	// Generate the texture ID
	glGenTextures(1, &mTextureID);

	//Bind the texture
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	//Generate the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//Unbind texture
	glBindTexture(GL_TEXTURE_2D, NULL);

	//Check for error
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Failed to load texture from %p pixels: %s\n", pixels, gluErrorString(error));
		return false;
	}

	return true;
}

bool LTexture::loadTextureFromFile(std::string path) {
	bool textureLoaded = false;

	ILuint imgID = 0;
	ilGenImages(1, &imgID);
	ilBindImage(imgID);

	ILboolean success = ilLoadImage(path.c_str());
	ILenum error = ilGetError();

	if (success == IL_TRUE)
	{
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		if (success == IL_TRUE)
		{
			textureLoaded = loadTextureFromPixels32((GLuint*)ilGetData(), (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT));
		}

		ilDeleteImages(1, &imgID);
	}
	else
	{
		printf("Error loading image %d: %s\n", error, "Something...");
	}

	if (!textureLoaded)
	{
		printf("Failed to load image: %s\n", path.c_str());
	}

	return textureLoaded;
}

void LTexture::freeTexture()
{
	if (mTextureID != 0)
	{
		glDeleteTextures(1, &mTextureID);
		mTextureID = 0;
	}

	mTextureWidth = 0;
	mTextureHeight = 0;
}

void LTexture::render(GLfloat x, GLfloat y)
{
	// If the texture exists
	if (mTextureID != 0)
	{
		//Remove any previous transformations
		glLoadIdentity();

		//Move to rendering point
		glTranslatef(x, y, 0.f);

		//Set texture ID
		glBindTexture(GL_TEXTURE_2D, mTextureID);

		//Render Textured quad
		glBegin(GL_QUADS);
		glTexCoord2f(0.f, 0.f);glVertex2f(0.f, 0.f);
		glTexCoord2f(1.f, 0.f);glVertex2f(mTextureWidth, 0.f);
		glTexCoord2f(1.f, 1.f);glVertex2f(mTextureWidth, mTextureHeight);
		glTexCoord2f(0.f, 1.f);glVertex2f(0.f, mTextureHeight);
		glEnd();
	}
}

GLuint LTexture::getTextureID()
{
	return mTextureID;
}

GLuint LTexture::textureWidth()
{
	return mTextureWidth;
}

GLuint LTexture::textureHeight()
{
	return mTextureHeight;
}