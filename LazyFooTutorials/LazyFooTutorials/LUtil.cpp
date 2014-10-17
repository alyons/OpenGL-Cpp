#include "LUtil.h"
#include "LTexture.h"

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

	return true;
}

bool loadMedia()
{
	const int CHECKERBOARD_WIDTH = 128;
	const int CHECKERBOARD_HEIGHT = 128;
	const int CHECKERBOARD_PIXEL_COUNT = CHECKERBOARD_HEIGHT * CHECKERBOARD_WIDTH;
	GLuint checkerBoard[CHECKERBOARD_PIXEL_COUNT];

	for (int i = 0; i < CHECKERBOARD_PIXEL_COUNT; i++)
	{
		GLubyte* colors = (GLubyte*)&checkerBoard[i];

		if (i / 128 & 16 ^ i % 128 & 16)
		{
			colors[0] = 0xFF;
			colors[1] = 0xFF;
			colors[2] = 0xFF;
			colors[3] = 0xFF;
		}
		else
		{
			colors[0] = 0xFF;
			colors[1] = 0x00;
			colors[2] = 0x00;
			colors[3] = 0xFF;
		}
	}

	if (!gTexture.loadTextureFromPixels32(checkerBoard, CHECKERBOARD_WIDTH, CHECKERBOARD_HEIGHT))
	{
		printf("Unable to load texture...\n");
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