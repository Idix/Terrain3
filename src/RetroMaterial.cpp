#include "RetroMaterial.h"

#include "TextShader.h"

RetroMaterial::RetroMaterial()
{
	m_Shader = new TextShader("shaders/retro");
	m_Shader->compile();
}
