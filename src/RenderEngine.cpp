#include "RenderEngine.h"

#include <math.h>

RenderEngine::RenderEngine()
{
    int width, height, i;
    glfwGetWindowSize(&width, &height);
    m_Camera.perspective(PI/2, width/height, 0.1, 50.0);
    showError("Camera");
    for(i=0; i<3; ++i) {
    	m_Tubes[i] = new Tube(8, 10);
    }
    showError("Tube");
    m_RetroMaterial = new RetroMaterial();

    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

RenderEngine::~RenderEngine()
{
    delete [] m_Tubes;
}

void RenderEngine::render(double elapsed)
{
	int i;
	m_Camera.forward(elapsed*5.0);
	int z = floor(m_Camera.getPosition().getZ()/10.0);
    m_Camera.initModelViewStack(m_MatrixStack);
    /*
    // World coordinates
    Math::Vector4 lightEyePosition = Math::Vector4(cos(currentTime)*10.0f, 0.0f, sin(currentTime)*10.0f, 1.0);
    // Eye coordinates
    lightEyePosition = m_MatrixStack.getCurrentMatrix() * lightEyePosition;
    */
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

	m_MatrixStack.push();
	m_MatrixStack.translate(0.0f, 0.0f, 10.0f * (z+1));
	for (i=0;i<3; i++) {
		m_RetroMaterial->setMvpMatrix(m_Camera.getProjection()*m_MatrixStack.getCurrentMatrix());
		m_RetroMaterial->setMvMatrix(m_MatrixStack.getCurrentMatrix());
		m_RetroMaterial->bind();

		m_Tubes[i]->render();
		m_MatrixStack.translate(0.0f, 0.0f, -10.0f);
	}
	m_MatrixStack.pop();

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
