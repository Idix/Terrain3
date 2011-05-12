#include "Triangle.h"

Triangle::Triangle()
{
    m_VertexBuffers = new GLuint[2];
    m_VertexCount = 3;

    GLfloat vVertex[] = {
        -0.5f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f };
    GLfloat vColor[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f };

    glGenBuffers(2, m_VertexBuffers);

    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_VertexCount * 3, vVertex, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_VertexCount * 4, vColor, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Triangle::~Triangle()
{
    glDeleteBuffers(2, m_VertexBuffers);
    delete [] m_VertexBuffers;
}
