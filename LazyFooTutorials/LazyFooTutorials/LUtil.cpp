#include "LUtil.h"
#include "LTexture.h"
#include <il/il.h>
#include <il/ilu.h>

//Some Texture
LTexture gTexture;

bool initGL()
{
	// Set the Viewport
	glViewport(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT);

	// Load Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);

	// Load Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set Clear color
	glClearColor(0.f, 0.f, 0.f, 1.f); // R, G, B, A

	//Enable Texturing
	glEnable(GL_TEXTURE_2D);

	// Check for GL Error
	GLenum glError = glGetError();
	if (glError != GL_NO_ERROR)
	{
		printf("Failed to initialize OpenGL: %s\n", gluErrorString(glError));
		return false;
	}

	ilInit();
	ilClearColor(255,255,255,000);
	ILenum ilError = ilGetError();

	if (ilError != IL_NO_ERROR)
	{
		printf("Failed to initialize ResIL: %s\n", iluErrorString(ilError));
		return false;
	}

	return true;
}

bool loadMedia()
{
	if (!gTexture.loadTextureFromFile("texture.png"))
	{
		printf("Unable to load texture from file...\n");
		return false;
	}

	return true;
}

void update()
{

}

void render()
{
	// Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	//Render checkerboard pattern
	GLfloat x = (SCREEN_WIDTH - gTexture.textureWidth()) / 2.f;
	GLfloat y = (SCREEN_HEIGHT - gTexture.textureHeight()) / 2.f;
	gTexture.render(x, y);

	// Update screen
	glutSwapBuffers();
}