#include "Tube.h"

#include <math.h>

Tube::Tube(unsigned int segments, unsigned int lengthSegments) : m_Segments(segments), m_LengthSegments(lengthSegments)
{
	unsigned int i, j, currentIndex = 0;
    m_VertexBuffers = new GLuint[2];
    m_VertexCount = (segments+1)*2*lengthSegments;

    GLfloat vVertex[m_VertexCount*4];
    GLfloat vTexCoord[m_VertexCount*2];

    for(j=0; j<lengthSegments; ++j)
    {
    	for(i=0; i<=segments; ++i)
    	{
    		vVertex[currentIndex+4] = vVertex[currentIndex+0] = cos(TWOPI*i/segments);
    		vVertex[currentIndex+5] = vVertex[currentIndex+1] = sin(TWOPI*i/segments);
    		vVertex[currentIndex+2] = j+0.0f;
    		vVertex[currentIndex+6] = j+1.0f;
    		vVertex[currentIndex+7] = vVertex[currentIndex+3] = 1.0f;

    		vTexCoord[currentIndex/2+0] = (j%2)+0.0f;
    		vTexCoord[currentIndex/2+2] = ((j+1)%2)+0.0f;
    		vTexCoord[currentIndex/2+1] = vTexCoord[currentIndex/2+3] = (i%2)+0.0f;

    		currentIndex += 8;
    	}
    }

    glGenBuffers(2, m_VertexBuffers);

    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_VertexCount * 4, vVertex, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_VertexCount * 2, vTexCoord, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Tube::~Tube()
{
    glDeleteBuffers(2, m_VertexBuffers);
    delete [] m_VertexBuffers;
}

void Tube::render() const
{
	unsigned int i, start=0;
	glBindVertexArray(m_VertexArray);
	for(i=0; i<m_LengthSegments; ++i)
	{
		glDrawArrays(GL_TRIANGLE_STRIP, start, (m_Segments+1)*2);
		start += (m_Segments+1)*2;
	}
	glBindVertexArray(0);
}
