#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "project.h"

class Renderable
{
    public:
        Renderable();
        virtual ~Renderable();
        virtual void render() const { render(GL_TRIANGLES); };
    protected:
        GLuint m_VertexArray;
        GLuint* m_VertexBuffers;
        GLuint m_VertexCount;
        void render(GLuint mode) const;
    private:

};

#endif // RENDERABLE_H
