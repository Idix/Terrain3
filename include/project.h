#ifndef PROJECT_H_INCLUDED
#define PROJECT_H_INCLUDED

#include <GL/glew.h>
#define GLFW_NO_GLU 1
#include <GL/glfw.h>

#ifndef PI
#define PI 3.14159265
#define TWOPI 6.28318531
#endif

bool showError(const char* additionalMessage);

#endif // PROJECT_H_INCLUDED
