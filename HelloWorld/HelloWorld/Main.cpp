#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include "Global.h"
#include "Utility.h"

using namespace std;

void changeViewport(int w, int h) {
	screenWidth = w;
	screenHeight = h;
	glViewport(0, 0, w, h);

	// Do not resize the elements, while still resizing the screen
	glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0, screenWidth, screenHeight, 0.0, 1.0, -1.0 );
}

void update() {
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glPushMatrix();

	 //Move to center of the screen
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
    glEnd();

    //Update screen
    glutSwapBuffers();
}

void runMainLoop(int val) {
	update();
	render();

	glutTimerFunc(1000 / FRAME_RATE, runMainLoop, val);
}

int main (int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("Hello, World!");
	
	if (!initGL()) {
		printf("Failed to start graphics library...\n");
		return 1;
	}

	glutReshapeFunc(changeViewport);
	glutKeyboardFunc(handleKeys);
	glutDisplayFunc(render);
	glutTimerFunc(1000 / FRAME_RATE, runMainLoop, 0);

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}

	glutMainLoop();
	return 0;
}