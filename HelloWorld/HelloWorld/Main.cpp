#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

using namespace std;

void changeViewport(int w, int h)
{
	glViewport(0, 0, w, h);
}