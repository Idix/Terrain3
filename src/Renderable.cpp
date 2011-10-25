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

void Renderable::render(GLuint mode) const
{
    if (m_VertexCount)
    {
        glBindVertexArray(m_VertexArray);
        showError("Before");
        glDrawArrays(mode, 0, m_VertexCount);
        showError("After");
        glBindVertexArray(0);
    }
}
