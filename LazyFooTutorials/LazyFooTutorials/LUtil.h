#include "LOpenGL.h"

// Screen Constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_FPS = 60;

bool initGL();
/*
Pre Condition:
 - A valid OpenGL Context
Post Condition:
 - Initializes matrices and clear color
 - Reports to console if there was an OpenGL error
 - Returns false if there was an error in initialization
Side Effects:
 - Projection matrix is set to identity matrix
 - Modelview matric is set to identity matrix
 - Matrix mode is set to modelview
 - Clear color is set to black
*/

bool loadMedia();

void update();
/*
 Pre Condition:
 - None
 Post Condition:
 - Does per frame logic
 Side Effects:
 - None
*/

void render();
/*
 Pre Condition:
 - A valid OpenGL context
 - Active modelview matrix
 Post Condition:
 - Renders the scene
 Side Effects:
 - Clears the color buffer
 - Swaps the front/back buffer
*/