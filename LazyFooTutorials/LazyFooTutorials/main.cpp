#include "LUtil.h"

void runMainLoop(int val);
/*
 Pre Condition:
 - Initialized GLUT
 Post Condition:
 - Calls the main loop function and sets itself to be called back in 1000 / SCREEN_FPS milliseconds
 Side Effect:
 - Sets glutTimerFunc
*/

int main(int argc, char* args[])
{
	// Initialize FreeGLUT
	glutInit(&argc, args);

	// Create OpenGL 2.1 Context
	glutInitContextVersion(2,1);

	//Create Double Buffered Window
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Lazy Foo's OpenGL Tutorial");

	// Do post Window/context creation initialization
	if (!initGL())
	{
		printf("Failed to initialize graphics library!\n");
		return 1;
	}

    glutKeyboardFunc(handleKeys);
	glutDisplayFunc(render);
	glutTimerFunc(1000 / SCREEN_FPS, runMainLoop, 0);

	glutMainLoop();

	return 0;
}

void runMainLoop(int val)
{
	update();
	render();

	glutTimerFunc(1000 / SCREEN_FPS, runMainLoop, val);
}