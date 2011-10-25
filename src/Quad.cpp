#include "Quad.h"

Quad::Quad()
{
    m_VertexBuffers = new GLuint[1];
    m_VertexCount = 4;

    GLfloat vVertex[] = {
    -1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, -1.0f, 0.0f, 1.0f};

    glGenBuffers(1, m_VertexBuffers);

    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_VertexCount * 4, vVertex, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Quad::~Quad()
{
    glDeleteBuffers(1, m_VertexBuffers);
    delete [] m_VertexBuffers;
}
