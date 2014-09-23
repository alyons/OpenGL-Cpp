#include "ShaderHelper.h"

// Private Functions
char* ShaderHelper::readFile(const char* filename) {
	FILE* fp = fopen(filename, "r");

	fseek(fp, 0, SEEK_END);
	long file_length = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* contents = new char[file_length];

	for(int i = 0; i < file_length; i++)
		contents[i] = 0;

	fread (contents, 1, file_length, fp);
	contents[file_length + 1] = '\0';
	fclose(fp);

	return contents;
}

GLuint ShaderHelper::makeVertexShader(const char* shaderSource) {
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, (const GLchar**)&shaderSource, NULL);
	glCompileShader(vertexShaderID);
	return vertexShaderID;
}

GLuint ShaderHelper::makeFragmentShader(const char* shaderSource) {
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, (const GLchar**)&shaderSource, NULL);
	glCompileShader(fragmentShaderID);
	return fragmentShaderID;
}

// Public Functions
GLuint ShaderHelper::loadVertexShader(const char* filename) {
	char* shaderSource = readFile(filename);
	GLuint vertexShaderID = makeVertexShader(shaderSource);
	return vertexShaderID;
}

GLuint ShaderHelper::loadFragmentShader(const char* filename) {
	char* shaderSource = readFile(filename);
	GLuint fragmentShaderID = makeFragmentShader(shaderSource);
	return fragmentShaderID;
}

GLuint ShaderHelper::makeShaderProgram(GLuint vertexShaderID, GLuint fragmentShaderID) {
	GLuint shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShaderID);
	glAttachShader(shaderID, fragmentShaderID);
	glLinkProgram(shaderID);
	return shaderID;
}