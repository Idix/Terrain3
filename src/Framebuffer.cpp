#include "Framebuffer.h"

Framebuffer::Framebuffer(int width, int height) : m_CurrentIndice(0)
{
    // Create framebuffer object
    glGenFramebuffers(1, &m_Fbo);
    bind();

    // Create depth renderbuffer
    glGenRenderbuffers(1, &m_DepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBuffer);
    resize(width, height);

    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBuffer);

    unbind();
}

Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &m_Fbo);
    glDeleteRenderbuffers(1, &m_DepthBuffer);
}

void Framebuffer::resize(int width, int height)
{
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, width, height);
}

void Framebuffer::attachTexture(const Texture* texture, int indice)
{
    if (indice < 0)
        indice = m_CurrentIndice;
    bind();
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+indice, GL_TEXTURE_2D, texture->getId(), 0);
    m_CurrentIndice = (indice+1) > m_CurrentIndice ?  indice+1 : m_CurrentIndice;
    unbind();
}
