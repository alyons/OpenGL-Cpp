#include "Texture.h"
#include <il/il.h>
#include <il/ilu.h>

Texture::Texture() {
	mTextureID = 0;

	mTextureWidth = 0;
	mTextureHeight = 0;

	mImageWidth = 0;
	mImageHeight = 0;
}

Texture::~Texture() {
	freeTexture();
}

bool Texture::loadTextureFromPixel32(GLuint* pixels, GLuint imgWidth, GLuint imgHeight, GLuint texWidth, GLuint texHeight) {
	freeTexture();

	mImageWidth = imgWidth;
	mImageHeight = imgHeight;
	mTextureWidth = texWidth;
	mTextureHeight = texHeight;

	glGenTextures(1, &mTextureID);

	glBindTexture(GL_TEXTURE_2D, mTextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mTextureWidth, mTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, NULL);

	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
		printf("Failed to load texture from %p pixels: %s\n", pixels, gluErrorString(error));
		return false;
	}

	return true;
}

void Texture::freeTexture() {
	if (mTextureID != 0)
	{
		glDeleteTextures(1, &mTextureID);
		mTextureID = 0;
	}

	mImageWidth = 0;
	mImageHeight = 0;
	mTextureWidth = 0;
	mTextureHeight = 0;
}

void Texture::render(GLfloat x, GLfloat y, RectangleF* clip) {
	if (mTextureID != 0)
	{
		glLoadIdentity();

		GLfloat texTop = 0.f;
		GLfloat texBottom = (GLfloat)mImageHeight / (GLfloat)mTextureHeight;
		GLfloat texLeft = 0.f;
		GLfloat texRight = (GLfloat)mImageWidth / (GLfloat)mTextureWidth;

		GLfloat quadWidth = mImageWidth;
		GLfloat quadHeight = mImageHeight;

		if (clip != NULL)
		{
			texLeft = clip->x / mTextureWidth;
			texRight = (clip->x + clip->width) / mTextureWidth;
			texTop = clip->y / mTextureHeight;
			texBottom = (clip->y + clip->height) / mTextureHeight;

			quadWidth = clip->width;
			quadHeight = clip->height;
		}

		glTranslatef(x, y, 0.f);

		glBindTexture(GL_TEXTURE_2D, mTextureID);

		glBegin(GL_QUADS);
			glTexCoord2f(texLeft, texTop);glVertex2f(0.f, 0.f);
			glTexCoord2f(texRight, texTop);glVertex2f(quadWidth, 0.f);
			glTexCoord2f(texRight, texBottom);glVertex2f(quadWidth, quadHeight);
			glTexCoord2f(texLeft, texBottom);glVertex2f(0.f, quadHeight);
		glEnd();
	}
}

GLuint Texture::getTextureID() {
	return mTextureID;
}

GLuint Texture::textureWidth() {
	return mTextureWidth;
}

GLuint Texture::textureHeight() {
	return mTextureHeight;
}

bool Texture::loadTextureFromFile(std::string path) {
	bool textureLoaded = false;

	ILuint imgID = 0;
	ilGenImages(1, &imgID);
	ilBindImage(imgID);

	ILboolean success = ilLoadImage(path.c_str());

	if (success == IL_TRUE)
	{
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		if (success == IL_TRUE)
		{
			GLuint imgWidth = (GLuint)ilGetInteger(IL_IMAGE_WIDTH);
			GLuint imgHeight = (GLuint)ilGetInteger(IL_IMAGE_HEIGHT);

			GLuint texWidth = powerOfTwo(imgWidth);
			GLuint texHeight = powerOfTwo(imgHeight);

			if (imgWidth != texWidth || imgHeight != texHeight)
			{
				iluImageParameter(ILU_PLACEMENT, ILU_UPPER_LEFT);
				iluEnlargeCanvas((int)texWidth, (int)texHeight, 1);
			}

			textureLoaded = loadTextureFromPixel32((GLuint*)ilGetData(), imgWidth, imgHeight, texWidth, texHeight);
		}

		ilDeleteImages(1, &imgID);
	}

	if (!textureLoaded)
		printf("Failed to load image: %s\n", path.c_str());

	return textureLoaded;
}

GLuint Texture::powerOfTwo(GLuint num)
{
	if (num != 0)
	{
		num--;
		num |= (num >> 1);
		num |= (num >> 2);
		num |= (num >> 4);
		num |= (num >> 8);
		num |= (num >> 16);
		num++;
	}

	return num;
}
