#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "project.h"
#include "Texture.h"

class Framebuffer
{
    public:
        Framebuffer(int width, int height);
        virtual ~Framebuffer();
        virtual void attachTexture(const Texture* texture, int indice = -1);
        void bind() { glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_Fbo); };
        void unbind() { glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); };
        void resize(int width, int height);
    protected:
        GLuint m_Fbo;
        GLuint m_DepthBuffer;
    private:
        GLuint m_CurrentIndice;
};

#endif // FRAMEBUFFER_H
