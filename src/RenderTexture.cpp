#include "RenderTexture.h"

RenderTexture::RenderTexture(int width, int height) : Texture()
{
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGBA, GL_FLOAT, 0);
    unbind();
}
