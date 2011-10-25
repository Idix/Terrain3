#include "PostMaterial.h"

#include "TextShader.h"

PostMaterial::PostMaterial(int width, int height)
{
    m_RenderTexture = new RenderTexture(width, height);
    m_Shader = new TextShader("shaders/postprocess");
    m_Shader->compile();
    appendTexture("postprocessing", m_RenderTexture);
}

PostMaterial::~PostMaterial()
{
    delete m_RenderTexture;
    delete m_Shader;
}
