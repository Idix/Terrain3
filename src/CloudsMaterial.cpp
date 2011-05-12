#include "CloudsMaterial.h"

CloudsMaterial::CloudsMaterial()
{
	TGATexture* texture;
	m_Shader = new TextShader("shaders/clouds");
	m_Shader->compile();
	texture = new TGATexture();
	texture->load("textures/EarthClouds.tga");
	appendTexture("cloudMap", texture);
}

void CloudsMaterial::setLightPosition(GLfloat x, GLfloat y, GLfloat z)
{
	m_Shader->setUniform3f("lightPosition", x, y, z);
}
