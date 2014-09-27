#include "Utility.h"
#include "Texture.h";

// Camera Position
GLfloat gCameraX = 0.f, gCameraY = 0.f;
Texture loadedTexture;

bool initGL() {
    glViewport(0.f, 0.f, screenWidth, screenHeight);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
	glOrtho( 0.0, screenWidth, screenHeight, 0.0, 1.0, -1.0 ); //Set coordinate to a similar system

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glClearColor( 0.f, 0.f, 0.f, 1.f );

	glEnable(GL_TEXTURE_2D);

    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf("Failed to initialize OpenGL: %s\n", gluErrorString(error));
        return false;
    }

	ilInit();
	iluInit();
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

bool loadMedia()
{
	if (!loadedTexture.loadTextureFromFile("HelloWorld/sonicadcance3.png"))
	{
		printf("Failed to load picture.\n");
		return false;
	}

	return true;
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glPushMatrix();

	//This is how we were drawing the squares...
	 /*//Move to center of the screen
	glTranslatef( screenWidth / 2.f, screenHeight / 2.f, 0.f );

    //Red quad
    glBegin( GL_QUADS );
        glColor3f( 1.f, 0.f, 0.f );
        glVertex2f( -screenWidth / 4.f, -screenHeight / 4.f );
        glVertex2f(  screenWidth / 4.f, -screenHeight / 4.f );
        glVertex2f(  screenWidth / 4.f,  screenHeight / 4.f );
        glVertex2f( -screenWidth / 4.f,  screenHeight / 4.f );
    glEnd();

    //Move to the right of the screen
    glTranslatef( screenWidth, 0.f, 0.f );

    //Green quad
    glBegin( GL_QUADS );
        glColor3f( 0.f, 1.f, 0.f );
        glVertex2f( -screenWidth / 4.f, -screenHeight / 4.f );
        glVertex2f(  screenWidth / 4.f, -screenHeight / 4.f );
        glVertex2f(  screenWidth / 4.f,  screenHeight / 4.f );
        glVertex2f( -screenWidth / 4.f,  screenHeight / 4.f );
    glEnd();

    //Move to the lower right of the screen
    glTranslatef( 0.f, screenHeight, 0.f );

    //Blue quad
    glBegin( GL_QUADS );
        glColor3f( 0.f, 0.f, 1.f );
        glVertex2f( -screenWidth / 4.f, -screenHeight / 4.f );
        glVertex2f(  screenWidth / 4.f, -screenHeight / 4.f );
        glVertex2f(  screenWidth / 4.f,  screenHeight / 4.f );
        glVertex2f( -screenWidth / 4.f,  screenHeight / 4.f );
    glEnd();

    //Move below the screen
    glTranslatef( -screenWidth, 0.f, 0.f );

    //Yellow quad
    glBegin( GL_QUADS );
        glColor3f( 1.f, 1.f, 0.f );
        glVertex2f( -screenWidth / 4.f, -screenHeight / 4.f );
        glVertex2f(  screenWidth / 4.f, -screenHeight / 4.f );
        glVertex2f(  screenWidth / 4.f,  screenHeight / 4.f );
        glVertex2f( -screenWidth / 4.f,  screenHeight / 4.f );
    glEnd();*/

	loadedTexture.render(0, 0);

    //Update screen
    glutSwapBuffers();
}

void update()
{
}