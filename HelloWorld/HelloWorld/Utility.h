#pragma once

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <il/il.h>
#include <il/ilu.h>
#include "Global.h"

bool initGL();

void handleKeys(unsigned char key, int x, int y);
/*
Pre Condition:
 -A valid OpenGL context
 -Active modelview matrix
Post Condition:
 -Changes center of rendering
Side Effects:
 -Different object may be visible
*/

void render();

void update();

bool loadMedia();