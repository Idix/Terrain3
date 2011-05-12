#include "MatrixStack.h"
#include <math.h>

MatrixStack::MatrixStack()
{
    reset();
}

void MatrixStack::reset()
{
    m_Stack[0].identity();
    m_CurrentDepth = 0;
}

void MatrixStack::reset(const Math::Matrix4& base)
{
    m_Stack[0].set(base);
    m_CurrentDepth = 0;
}

void MatrixStack::push()
{
    if (m_CurrentDepth+1<MAXMATRIXSTACKDEPTH)
    {
        ++m_CurrentDepth;
        m_Stack[m_CurrentDepth].set(m_Stack[m_CurrentDepth-1]);
    }
}

void MatrixStack::pop()
{
    if (m_CurrentDepth>=1)
        --m_CurrentDepth;
}

void MatrixStack::translate(GLfloat x, GLfloat y, GLfloat z)
{
    m_Stack[m_CurrentDepth] *= Math::Matrix4::createTranslation(x, y, z);
}

void MatrixStack::rotate(GLfloat x, GLfloat y, GLfloat z, GLfloat angle)
{
	m_Stack[m_CurrentDepth] *= Math::Matrix4::createRotation(x, y, z, angle);
}

void MatrixStack::scale(GLfloat x, GLfloat y, GLfloat z)
{
	m_Stack[m_CurrentDepth] *= Math::Matrix4::createScale(x, y, z);
}
