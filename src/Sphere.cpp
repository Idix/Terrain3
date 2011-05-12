#include "Sphere.h"

#include <math.h>
#include <assert.h>

Sphere::Sphere(int steps)
{
    int i, j, currentIndex = 0;
    GLfloat circleRadius;
    steps = steps < 4 ? 4 : steps;
    m_Steps = steps;
    m_VertexBuffers = new GLuint[2];
    m_VertexCount = 2*steps*(steps-1);

    GLfloat vVertex[m_VertexCount*4];
    GLfloat vCoord[m_VertexCount*2];

    for(i=0; i<steps; ++i)
    {
		vVertex[currentIndex+0] = 0.0f;
		vVertex[currentIndex+1] = 1.0f;
		vVertex[currentIndex+2] = 0.0f;
		vVertex[currentIndex+3] = 1.0f;
		vCoord[currentIndex/2+0] = 1.0f-(i+1.0f)/steps;
		vCoord[currentIndex/2+1] = 1.0f;
		currentIndex += 4;
        for(j=1; j<steps-1; ++j)
        {
            circleRadius = sin(j * PI / (steps-1));

            vVertex[currentIndex+0] = cos((i+1)*(TWOPI / steps))*circleRadius;
            vVertex[currentIndex+1] = cos(j * PI / (steps-1));
            vVertex[currentIndex+2] = sin((i+1)*(TWOPI / steps))*circleRadius;
            vVertex[currentIndex+3] = 1.0f;
            vCoord[currentIndex/2+0] = 1.0f-(i+2.0f)/steps;
            vCoord[currentIndex/2+1] = (steps-1.0f-j)/(steps-1.0f);
            currentIndex += 4;

            vVertex[currentIndex+0] = cos(i*(TWOPI / steps))*circleRadius;
            vVertex[currentIndex+1] = cos(j * PI / (steps-1));
            vVertex[currentIndex+2] = sin(i*(TWOPI / steps))*circleRadius;
            vVertex[currentIndex+3] = 1.0f;
            vCoord[currentIndex/2+0] = 1.0f-(i+1.0f)/steps;
            vCoord[currentIndex/2+1] = (steps-1.0f-j)/(steps-1.0f);
            currentIndex += 4;
        }
		vVertex[currentIndex+0] =  0.0f;
		vVertex[currentIndex+1] = -1.0f;
		vVertex[currentIndex+2] =  0.0f;
		vVertex[currentIndex+3] = 1.0f;
		vCoord[currentIndex/2+0] = 1.0f-(i+1.0f)/steps;
		vCoord[currentIndex/2+1] = 0.0f;
		assert(currentIndex<(int)m_VertexCount*4);
		currentIndex += 4;
    }

    glGenBuffers(3, m_VertexBuffers);

    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_VertexCount * 4, vVertex, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    // Normals ( same as vertex in a sphere :))
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), 0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffers[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_VertexCount * 2, vCoord, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Sphere::~Sphere()
{
    glDeleteBuffers(2, m_VertexBuffers);
    delete [] m_VertexBuffers;
}

void Sphere::render() const
{
    unsigned int i, start;
    glBindVertexArray(m_VertexArray);
    start = 0;
    for(i=0; i<m_Steps; ++i)
    {
        glDrawArrays(GL_TRIANGLE_STRIP, start, 2*(m_Steps-1));
        start += 2*(m_Steps-1);
    }
    glBindVertexArray(0);
}
