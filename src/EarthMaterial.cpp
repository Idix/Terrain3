#include "EarthMaterial.h"

EarthMaterial::EarthMaterial()
{
	TGATexture* texture;
	m_Shader = new TextShader("shaders/earth");
	m_Shader->compile();
	showError("shader compile");

	m_Shader->setUniform3f("specularColor", 0.98f, 0.89f, 0.88f);

	texture = new TGATexture();
	texture->load("textures/EarthMap.tga");
	appendTexture("colorMap", texture);
	showError("texture colorMap");

	texture = new TGATexture();
	texture->load("textures/EarthNight.tga");
	appendTexture("nightColorMap", texture);
	showError("texture nightColorMap");

	texture = new TGATexture();
	texture->load("textures/EarthSpec.tga");
	appendTexture("specularMap", texture);

	texture = new TGATexture();
	texture->load("textures/EarthClouds.tga");
	appendTexture("cloudMap", texture);
}

void EarthMaterial::setLightPosition(GLfloat x, GLfloat y, GLfloat z)
{
	m_Shader->setUniform3f("lightPosition", x, y, z);
}

void EarthMaterial::recompileShader()
{
	Material::recompileShader();
	m_Shader->setUniform3f("specularColor", 0.98f, 0.89f, 0.88f);
}
