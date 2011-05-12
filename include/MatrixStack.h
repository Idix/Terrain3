#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H

#include "project.h"
#include "Math/Matrix4.h"
#include "Math/Vector3D.h"

#define MAXMATRIXSTACKDEPTH 16

class MatrixStack
{
    public:
        MatrixStack();
        void reset();
        void reset(const Math::Matrix4& base);
        void push();
        void pop();
        void translate(GLfloat x, GLfloat y, GLfloat z);
        void rotate(GLfloat x, GLfloat y, GLfloat z, GLfloat angle);
        void scale(GLfloat x, GLfloat y, GLfloat z);
        inline void rotate(const Math::Vector3D& axis, GLfloat angle) { rotate(axis.getX(), axis.getY(), axis.getZ(), angle); };
        inline const Math::Matrix4& getCurrentMatrix() { return m_Stack[m_CurrentDepth]; };
    protected:
    private:
        Math::Matrix4 m_Stack[MAXMATRIXSTACKDEPTH];
        unsigned int m_CurrentDepth;
};

#endif // MATRIXSTACK_H
