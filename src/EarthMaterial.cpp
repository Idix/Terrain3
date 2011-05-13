#include "EarthMaterial.h"

EarthMaterial::EarthMaterial()
{
	PngTexture* texture;
	m_Shader = new TextShader("shaders/earth");
	m_Shader->compile();
	showError("shader compile");

	m_Shader->setUniform3f("specularColor", 0.98f, 0.89f, 0.88f);

	texture = new PngTexture();
	texture->load("textures/EarthMap.png");
	appendTexture("colorMap", texture);
	showError("texture colorMap");

	texture = new PngTexture();
	texture->load("textures/EarthNight.png");
	appendTexture("nightColorMap", texture);
	showError("texture nightColorMap");

	texture = new PngTexture();
	texture->load("textures/EarthSpec.png");
	appendTexture("specularMap", texture);

	texture = new PngTexture();
	texture->load("textures/EarthClouds.png");
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
