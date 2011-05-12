#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "project.h"

class Renderable
{
    public:
        Renderable();
        virtual ~Renderable();
        virtual void render() const;
    protected:
        GLuint m_VertexArray;
        GLuint* m_VertexBuffers;
        GLuint m_VertexCount;
    private:

};

#endif // RENDERABLE_H
