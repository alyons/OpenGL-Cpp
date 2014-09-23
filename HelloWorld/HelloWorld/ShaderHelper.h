#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

class ShaderHelper abstract sealed
{
private:
	char* readFile(const char* filename);
	GLuint makeVertexShader(const char* shaderSource);
	GLuint makeFragmentShader(const char* shaderSource);
public:
	GLuint loadVertexShader(const char* filename);
	GLuint loadFragmentShader(const char* filename);
	GLuint makeShaderProgram(GLuint vertexShaderID, GLuint fragmentShaderID);
};