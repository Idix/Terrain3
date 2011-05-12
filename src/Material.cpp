#include "Material.h"

Material::Material() : m_Shader(0), m_TextureCount(0)
{
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &m_MaxTextureCount);
	m_TextureList = new const Texture*[m_MaxTextureCount];
	m_TextureName = new const char*[m_MaxTextureCount];
}

Material::~Material()
{
	delete [] m_TextureList;
	delete [] m_TextureName;
	delete m_Shader;
}

void Material::recompileShader()
{
	int i;
	m_Shader->compile();
	for(i=0; i<m_TextureCount; ++i)
			m_Shader->setUniform1i(m_TextureName[i], i);
}

void Material::setMvpMatrix(const GLfloat* matrix)
{
	m_Shader->setUniformMatrix4("mvpMatrix", matrix);
}

void Material::setMvMatrix(const GLfloat* matrix)
{
	m_Shader->setUniformMatrix4("mvMatrix", matrix);
}

void Material::setNormalMatrix(const GLfloat* matrix)
{
	m_Shader->setUniformMatrix3("normalMatrix", matrix);
}

void Material::bind()
{
	int i;
	for(i=0; i<m_TextureCount; ++i)
	{
		glActiveTexture(GL_TEXTURE0+i);
		m_TextureList[i]->bind();
	}
	for(; i<m_MaxTextureCount; ++i)
	{
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if (m_Shader)
		m_Shader->use(true);
}

bool Material::appendTexture(const char* textureName, const Texture* textureObject)
{
	if (m_TextureCount >= m_MaxTextureCount)
		return false;
	m_TextureList[m_TextureCount] = textureObject;
	m_TextureName[m_TextureCount] = textureName;
	m_Shader->setUniform1i(textureName, m_TextureCount);
	++m_TextureCount;
	return true;
}
