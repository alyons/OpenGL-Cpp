#include "Utility.h"
#include "Texture.h";

// Camera Position
GLfloat gCameraX = 0.f, gCameraY = 0.f;
Texture loadedTexture;

bool initGL() {
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
	glOrtho( 0.0, screenWidth, screenHeight, 0.0, 1.0, -1.0 ); //Set coordinate to a similar system

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glClearColor( 0.f, 0.f, 0.f, 1.f );

    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf("Failed to initialize OpenGL: %s\n", gluErrorString(error));
        return false;
    }

	ilInit();
	ilClearColour(255, 255, 255, 000);

	ILenum ilError = ilGetError();
	if (ilError != IL_NO_ERROR)
	{
		printf("Failed to initialize ResIL: %s\n", iluErrorString(ilError));
		return false;
	}

    return true;
}

void handleKeys(unsigned char key, int x, int y) {

	if (key == 'w')
	{
		gCameraY -= 16.f;
	}
	else if (key == 's')
	{
		gCameraY += 16.f;
	}
	else if (key == 'a')
	{
		gCameraX -= 16.f;
	}
	else if (key == 'd')
	{
		gCameraX += 16.f;
	}
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glLoadIdentity();

	glTranslatef(-gCameraX, -gCameraY, 0.f);

	glPushMatrix();
}
