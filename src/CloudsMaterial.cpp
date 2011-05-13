#include "CloudsMaterial.h"

CloudsMaterial::CloudsMaterial()
{
	PngTexture* texture;
	m_Shader = new TextShader("shaders/clouds");
	m_Shader->compile();
	texture = new PngTexture();
	texture->load("textures/EarthClouds.png");
	appendTexture("cloudMap", texture);
}

void CloudsMaterial::setLightPosition(GLfloat x, GLfloat y, GLfloat z)
{
	m_Shader->setUniform3f("lightPosition", x, y, z);
}
