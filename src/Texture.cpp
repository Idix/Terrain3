#include "Texture.h"

Texture::Texture(void)
{
	glGenTextures(1, &id);
}

Texture::~Texture(void)
{
	glDeleteTextures(1, &id);
	glfwFreeImage(&image);
}

bool Texture::load(bool mipmap)
{
    bind();
    showError("texture bind");
    bool result = glfwLoadTextureImage2D(&image, 0);
    showError("texture loadTexture");
    if (mipmap)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }
    unbind();
    return result;
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind(void)
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getId(void) const
{
	return id;
}
