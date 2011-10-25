#include "RenderEngine.h"

#include <math.h>

RenderEngine::RenderEngine(int width, int height)
{
	resize(width, height);
    m_Renderable = new Sphere(98);
    m_PostQuad = new Quad();
    showError("Sphere");
    m_EarthMaterial = new EarthMaterial();
    m_CloudsMaterial = new CloudsMaterial();
    m_SunMaterial = new SunMaterial();
    m_PostMaterial = new PostMaterial(width, height);
    showError("Material");

    m_Framebuffer = new Framebuffer(width, height);
    m_Framebuffer->attachTexture(m_PostMaterial->getRenderTexture());
    showError("Framebuffer");

    m_Sun = new Sphere(24);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

RenderEngine::~RenderEngine()
{
    delete m_Renderable;
    delete m_PostQuad;
    delete m_EarthMaterial;
    delete m_CloudsMaterial;
    delete m_SunMaterial;
    delete m_PostMaterial;
    delete m_Sun;


}

void RenderEngine::resize(int width, int height)
{
    m_Camera.perspective(PI/2, width/height, 0.1, 10.0);

    showError("Camera");
}

void RenderEngine::render(double elapsed)
{
    m_Framebuffer->bind();
    pass1(elapsed);
    m_Framebuffer->unbind();
    pass2(elapsed);

    glfwSwapBuffers();
}

void RenderEngine::pass1(double elapsed)
{
	GLfloat currentTime = glfwGetTime()*0.1f;
    m_Camera.initModelViewStack(m_MatrixStack);
    // World coordinates
    Math::Vector4 lightEyePosition = Math::Vector4(cos(currentTime)*10.0f, 0.0f, sin(currentTime)*10.0f, 1.0);
    // Eye coordinates
    lightEyePosition = m_MatrixStack.getCurrentMatrix() * lightEyePosition;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_MatrixStack.push();

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

    m_MatrixStack.pop();
    m_MatrixStack.push();
    m_MatrixStack.rotate(0.0f, 1.0f, 0.0f, -currentTime);
    m_MatrixStack.translate(9.0f, 0.0f, 0.0f);
    //m_MatrixStack.scale(0.0418f, 0.0418f, 0.0418f);
    m_MatrixStack.scale(0.5f, 0.5f, 0.5f);

	m_SunMaterial->setMvpMatrix(m_Camera.getProjection()*m_MatrixStack.getCurrentMatrix());
	m_SunMaterial->bind();
	m_Sun->render();

	m_MatrixStack.pop();
}

void RenderEngine::pass2(double elapsed)
{
    glDisable(GL_DEPTH_TEST);

    m_PostMaterial->bind();
    m_PostQuad->render();

    glEnable(GL_DEPTH_TEST);

}

Camera& RenderEngine::getCamera()
{
    return m_Camera;
}

void RenderEngine::recompileShaders()
{
	m_EarthMaterial->recompileShader();
}
