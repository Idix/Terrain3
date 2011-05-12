#include "Renderable.h"

Renderable::Renderable() : m_VertexCount(0)
{
    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);
}

Renderable::~Renderable()
{
    glDeleteVertexArrays(1, &m_VertexArray);
}

void Renderable::render() const
{
    if (m_VertexCount)
    {
        glBindVertexArray(m_VertexArray);
        glDrawArrays(GL_TRIANGLES, 0, m_VertexCount);
        glBindVertexArray(0);
    }
}
