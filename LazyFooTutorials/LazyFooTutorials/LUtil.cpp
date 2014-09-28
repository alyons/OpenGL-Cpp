#include "LUtil.h"

bool initGL()
{
	// Load Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Load Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set Clear color
	glClearColor(0.f, 0.f, 0.f, 1.f); // R, G, B, A

	// Check for GL Error
	GLenum glError = glGetError();
	if (glError != GL_NO_ERROR)
	{
		printf("Failed to initialize OpenGL: %s\n", gluErrorString(glError));
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

	glBegin(GL_QUADS);
		glVertex2f( -0.5f, -0.5f );
        glVertex2f(  0.5f, -0.5f );
        glVertex2f(  0.5f,  0.5f );
        glVertex2f( -0.5f,  0.5f );
	glEnd();

	glutSwapBuffers();
}