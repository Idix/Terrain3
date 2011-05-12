#pragma once

#include "project.h"
#include <iostream>

class Texture
{
private:
	GLuint id;
	GLint lastTex;
protected:
	Texture(void);

    GLFWimage image;
	bool load(bool mipmap = true);
public:
	~Texture(void);
	void bind() const;
	static void unbind(void);
	GLuint getId(void) const;
};
