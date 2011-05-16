#include "RenderEngine.h"

#include <math.h>

RenderEngine::RenderEngine()
{
    int width, height;
    glfwGetWindowSize(&width, &height);
    m_Camera.perspective(PI/2, width/height, 0.1, 10.0);
    showError("Camera");
    m_Renderable = new Tube(8, 4);
    showError("Tube");
    m_RetroMaterial = new RetroMaterial();

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

RenderEngine::~RenderEngine()
{
    delete m_Renderable;
}

void RenderEngine::render(double elapsed)
{
	GLfloat currentTime = glfwGetTime()*0.2f;
    m_Camera.initModelViewStack(m_MatrixStack);
    // World coordinates
    Math::Vector4 lightEyePosition = Math::Vector4(cos(currentTime)*10.0f, 0.0f, sin(currentTime)*10.0f, 1.0);
    // Eye coordinates
    lightEyePosition = m_MatrixStack.getCurrentMatrix() * lightEyePosition;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*
	m_EarthMaterial->setMvpMatrix(m_Camera.getProjection()*m_MatrixStack.getCurrentMatrix());
	m_EarthMaterial->setMvMatrix(m_MatrixStack.getCurrentMatrix());
	m_EarthMaterial->setLightPosition(lightEyePosition.extractVector3());
    m_EarthMaterial->bind();
    m_Renderable->render();

    m_MatrixStack.scale(1.002f, 1.002f, 1.002f);
	m_CloudsMaterial->setMvpMatrix(m_Camera.getProjection()*m_MatrixStack.getCurrentMatrix());
	m_CloudsMaterial->setMvMatrix(m_MatrixStack.getCurrentMatrix());
    m_CloudsMaterial->setLightPosition(lightEyePosition.extractVector3());
    m_CloudsMaterial->bind();
    m_Renderable->render();
    */

	m_RetroMaterial->setMvpMatrix(m_Camera.getProjection()*m_MatrixStack.getCurrentMatrix());
	m_RetroMaterial->setMvMatrix(m_MatrixStack.getCurrentMatrix());
    m_RetroMaterial->bind();

    m_Renderable->render();

    glfwSwapBuffers();
}

Camera& RenderEngine::getCamera()
{
    return m_Camera;
}

void RenderEngine::recompileShaders()
{
	m_EarthMaterial->recompileShader();
}
