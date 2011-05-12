#pragma once

#include "project.h"
#include <iostream>

class Shader
{
private:
	bool compiled;
	GLuint id;
	GLuint vertexId;
	GLuint fragmentId;

	void printShaderInfoLog(GLuint obj);
	void printProgramInfoLog(void);
protected:
	GLsizei vertexCount;
	const GLchar **vertexString;
 	const GLint *vertexLength;

	GLsizei fragmentCount;
	const GLchar **fragmentString;
 	const GLint *fragmentLength;

	virtual void copyVertex(void) = 0;
	virtual void copyFragment(void) = 0;
	virtual void afterCompile(bool successfulCompile);
	GLuint getId(void) const;
public:
	Shader(void);
	~Shader(void);
	bool compile(void);
	virtual void use(bool useShader) const;
	bool setUniformMatrix4(const char* name, const GLfloat* value, GLsizei count = 1, GLboolean transpose = false);
	bool setUniformMatrix3(const char* name, const GLfloat* value, GLsizei count = 1, GLboolean transpose = false);
	bool setUniform3f(const char* name, GLfloat x, GLfloat y, GLfloat z);
	bool setUniform1i(const char* name, GLint v0);
};
