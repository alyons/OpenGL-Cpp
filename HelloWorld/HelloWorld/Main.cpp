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

	if (!loadMedia())
	{
		printf("Failed to load media!\n");
		return 2;
	}

	glutReshapeFunc(changeViewport);
	glutKeyboardFunc(handleKeys);
	glutDisplayFunc(render);
	glutTimerFunc(1000 / FRAME_RATE, runMainLoop, 0);

	/*GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}*/

	glutMainLoop();
	return 0;
}