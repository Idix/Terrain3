#include <GL/glew.h>
#define GLFW_NO_GLU 1
#include <GL/glfw.h>
#include <iostream>

#include <stdlib.h>

#include "RenderEngine.h"
#include "Camera.h"

const double movementSpeed = 1.0;

RenderEngine* engine;
bool running = true;
bool captureMouse = false;

bool showError(const char* additionalMessage)
{
    GLenum err;
    bool error = false;
    while((err = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << additionalMessage << ": ";
        switch(err)
        {
            case GL_INVALID_ENUM:
                std::cerr << "An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
                break;
            case GL_INVALID_VALUE:
                std::cerr << "A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
                break;
            case GL_INVALID_OPERATION:
                std::cerr << "The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                std::cerr << "The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
                break;
            case GL_OUT_OF_MEMORY:
                std::cerr << "There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded." << std::endl;
                break;
            default:
                std::cerr << "Error: " << err << std::endl;
                break;
        }
        error = true;
    }

    return error;
}

void keyboard(int key, int action)
{
    if (action == GLFW_RELEASE)
        return;
	switch (key) {
		case GLFW_KEY_ESC:
			running = false;
			break;
        case 'R':
            engine->recompileShaders();
            break;
		case GLFW_KEY_SPACE:
			captureMouse = !captureMouse;
			if (captureMouse)
			{
				int width, height;
				glfwGetWindowSize( &width, &height );
				glfwSetMousePos(width/2, height/2);
			}
			break;
/*
		case 38: // 1
			terrain->fault(FAULT_STEP);
			gui->incIterations();
			break;
		case 233: // 2
			terrain->fault(FAULT_SIN);
			gui->incIterations();
			break;
		case 34: // 3
			terrain->fault(FAULT_COS);
			gui->incIterations();
			break;
		case 102: // F
			wireframe = !wireframe;
			engine->setWireframe(wireframe);
			break;
		case 114: // R
			terrain->reset();
			gui->resetIterations();
			break;
        case 224: // 0
			terrain->smooth();
            break;
		case 110: // N
			normal = !normal;
			terrain->showNormals(normal);
			break;
		case 45: // - (numpad)
			terrain->decal(-1.0);
			break;
		case 43: // + (numpad)
			terrain->decal(1.0);
			break;
        case 9: // Tab
			shaderIdx = (shaderIdx+1)%(sizeof(listShaders)/sizeof(Shader*));
			gui->setShaderIdx(shaderIdx);
			terrain->setShader(listShaders[shaderIdx]);
            break;
		case 119: // W
			water = !water;
			engine->showWater(water);
			break;
		case 32: // SPACE
			rotateSun = !rotateSun;
			sun->rotating(rotateSun);
			break;
*/
		default:
            std::cout << "Key: " << key << std::endl;
			break;
	}
}

int main()
{
    const char* msg;
    GLenum err;
    int width, height;
    double lastTick = 0.0;
    double elapsed;
    int mouseX, mouseY, diffX, diffY;

    glfwInit();

    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    if( !glfwOpenWindow( 1024, 1024, 0, 0, 0, 0, 0, 0, GLFW_WINDOW ) )
    {
        glfwTerminate();
        return 0;
    }

    //glfwDisable(GLFW_MOUSE_CURSOR);

    err = glewInit();
    if (GLEW_OK != err)
    {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
    }

    glfwSetWindowTitle("GLFW Application");

    msg = (char*)glGetString(GL_VENDOR);
    std::cout << "Vendor: " << msg << std::endl;
    msg = (char*)glGetString(GL_RENDERER);
    std::cout << "Renderer: " << msg << std::endl;
    msg = (char*)glGetString(GL_VERSION);
    std::cout << "Version: " << msg << std::endl;
    msg = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
    std::cout << "Shading version: " << msg << std::endl;

    srand((unsigned int) time(NULL));

    showError("Before init");
    engine = new RenderEngine();
    showError("After init");

    glfwSetKeyCallback(keyboard);

    while(running)
    {
        glfwGetWindowSize( &width, &height );
        height = height > 0 ? height : 1;

        glViewport( 0, 0, width, height );

        elapsed = glfwGetTime() - lastTick;
        lastTick = glfwGetTime();
        if (glfwGetKey('Q'))
            engine->getCamera().left(elapsed * movementSpeed);
        else if (glfwGetKey('D'))
            engine->getCamera().right(elapsed * movementSpeed);
        if (glfwGetKey('Z'))
            engine->getCamera().forward(elapsed * movementSpeed);
        else if (glfwGetKey('S'))
            engine->getCamera().backward(elapsed * movementSpeed);
		if (captureMouse)
		{
			glfwGetMousePos(&mouseX, &mouseY);
			glfwSetMousePos(width/2, height/2);
			diffX = mouseX - width/2;
			diffY = mouseY - height/2;
			if (diffX)
				engine->getCamera().rotateLeftRight(diffX * 0.1);
			if (diffY)
				engine->getCamera().rotateUpDown(diffY * 0.1);
		}
        engine->render(elapsed);

        // exit if ESC was pressed or window was closed
        running &= glfwGetWindowParam(GLFW_OPENED);

        running &= !showError("Running");
    }
    glfwTerminate();

    return 0;
}
