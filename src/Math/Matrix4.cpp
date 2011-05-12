#include "Math/Matrix4.h"

#include <string.h>
#include <math.h>

namespace Math
{
    Matrix4::Matrix4()
    {
        memset(m_Matrix, 0, sizeof(GLfloat)*16);
    }

    void Matrix4::set(const Matrix4& other)
    {
        memcpy(m_Matrix, other.m_Matrix, sizeof(GLfloat)*16);
    }

    void Matrix4::set(unsigned int i, unsigned int j, GLfloat newValue)
    {
        if (i<1 || i>4 || j<1 || j>4)
            throw "Out of bound";
        m_Matrix[i-1+(j-1)*4] = newValue;
    }

    GLfloat& Matrix4::operator[](unsigned int index)
    {
        index = index<16 ? index : 15;
        return m_Matrix[index];
    }

    void Matrix4::identity()
    {
        memset(m_Matrix, 0, sizeof(GLfloat)*16);
        m_Matrix[0] = 1.0;
        m_Matrix[5] = 1.0;
        m_Matrix[10] = 1.0;
        m_Matrix[15] = 1.0;
    }

    const GLfloat* Matrix4::getRaw() const
    {
        return m_Matrix;
    }

    const GLfloat* Matrix4::getMatrix3Raw()
    {
    	memcpy(m_NormalMatrix, m_Matrix, sizeof(GLfloat)*3);
    	memcpy(m_NormalMatrix+3, m_Matrix+4, sizeof(GLfloat)*3);
    	memcpy(m_NormalMatrix+6, m_Matrix+8, sizeof(GLfloat)*3);

    	return m_NormalMatrix;
    }

    Matrix4 Matrix4::multiply(const Matrix4& other) const
    {
        Matrix4 result;
        result.m_Matrix[0] = m_Matrix[0]*other.m_Matrix[0] + m_Matrix[4]*other.m_Matrix[1] + m_Matrix[8]*other.m_Matrix[2] + m_Matrix[12]*other.m_Matrix[3];
        result.m_Matrix[1] = m_Matrix[1]*other.m_Matrix[0] + m_Matrix[5]*other.m_Matrix[1] + m_Matrix[9]*other.m_Matrix[2] + m_Matrix[13]*other.m_Matrix[3];
        result.m_Matrix[2] = m_Matrix[2]*other.m_Matrix[0] + m_Matrix[6]*other.m_Matrix[1] + m_Matrix[10]*other.m_Matrix[2] + m_Matrix[14]*other.m_Matrix[3];
        result.m_Matrix[3] = m_Matrix[3]*other.m_Matrix[0] + m_Matrix[7]*other.m_Matrix[1] + m_Matrix[11]*other.m_Matrix[2] + m_Matrix[15]*other.m_Matrix[3];

        result.m_Matrix[4] = m_Matrix[0]*other.m_Matrix[4] + m_Matrix[4]*other.m_Matrix[5] + m_Matrix[8]*other.m_Matrix[6] + m_Matrix[12]*other.m_Matrix[7];
        result.m_Matrix[5] = m_Matrix[1]*other.m_Matrix[4] + m_Matrix[5]*other.m_Matrix[5] + m_Matrix[9]*other.m_Matrix[6] + m_Matrix[13]*other.m_Matrix[7];
        result.m_Matrix[6] = m_Matrix[2]*other.m_Matrix[4] + m_Matrix[6]*other.m_Matrix[5] + m_Matrix[10]*other.m_Matrix[6] + m_Matrix[14]*other.m_Matrix[7];
        result.m_Matrix[7] = m_Matrix[3]*other.m_Matrix[4] + m_Matrix[7]*other.m_Matrix[5] + m_Matrix[11]*other.m_Matrix[6] + m_Matrix[15]*other.m_Matrix[7];

        result.m_Matrix[8] = m_Matrix[0]*other.m_Matrix[8] + m_Matrix[4]*other.m_Matrix[9] + m_Matrix[8]*other.m_Matrix[10] + m_Matrix[12]*other.m_Matrix[11];
        result.m_Matrix[9] = m_Matrix[1]*other.m_Matrix[8] + m_Matrix[5]*other.m_Matrix[9] + m_Matrix[9]*other.m_Matrix[10] + m_Matrix[13]*other.m_Matrix[11];
        result.m_Matrix[10] = m_Matrix[2]*other.m_Matrix[8] + m_Matrix[6]*other.m_Matrix[9] + m_Matrix[10]*other.m_Matrix[10] + m_Matrix[14]*other.m_Matrix[11];
        result.m_Matrix[11] = m_Matrix[3]*other.m_Matrix[8] + m_Matrix[7]*other.m_Matrix[9] + m_Matrix[11]*other.m_Matrix[10] + m_Matrix[15]*other.m_Matrix[11];

        result.m_Matrix[12] = m_Matrix[0]*other.m_Matrix[12] + m_Matrix[4]*other.m_Matrix[13] + m_Matrix[8]*other.m_Matrix[14] + m_Matrix[12]*other.m_Matrix[15];
        result.m_Matrix[13] = m_Matrix[1]*other.m_Matrix[12] + m_Matrix[5]*other.m_Matrix[13] + m_Matrix[9]*other.m_Matrix[14] + m_Matrix[13]*other.m_Matrix[15];
        result.m_Matrix[14] = m_Matrix[2]*other.m_Matrix[12] + m_Matrix[6]*other.m_Matrix[13] + m_Matrix[10]*other.m_Matrix[14] + m_Matrix[14]*other.m_Matrix[15];
        result.m_Matrix[15] = m_Matrix[3]*other.m_Matrix[12] + m_Matrix[7]*other.m_Matrix[13] + m_Matrix[11]*other.m_Matrix[14] + m_Matrix[15]*other.m_Matrix[15];

        return result;
    }

    Vector4 Matrix4::multiply(const Vector4& vector) const
    {
    	return Vector4(	m_Matrix[0]*vector[0] + m_Matrix[4]*vector[1] + m_Matrix[8]*vector[2] + m_Matrix[12]*vector[3],
						m_Matrix[1]*vector[0] + m_Matrix[5]*vector[1] + m_Matrix[9]*vector[2] + m_Matrix[13]*vector[3],
						m_Matrix[2]*vector[0] + m_Matrix[6]*vector[1] + m_Matrix[10]*vector[2] + m_Matrix[14]*vector[3],
						m_Matrix[3]*vector[0] + m_Matrix[7]*vector[1] + m_Matrix[11]*vector[2] + m_Matrix[15]*vector[3]);
    }

    Matrix4& Matrix4::operator*=(const Matrix4& other)
    {
        set(multiply(other));
        return *this;
    }

    Matrix4 Matrix4::createPerspective(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far)
    {
    	Matrix4 perspectiveMatrix;

        GLfloat right = tan(0.5f * fov)*near;
        right = right < 0 ? right*-1.0f : right;
        GLfloat top = right / aspect;
        perspectiveMatrix.m_Matrix[0] = near / right;
        perspectiveMatrix.m_Matrix[5] = near / top;
        perspectiveMatrix.m_Matrix[10] = -(far+near)/(far-near);
        perspectiveMatrix.m_Matrix[11] = -1.0f;
        perspectiveMatrix.m_Matrix[14] = -2.0f*far*near/(far-near);

        return perspectiveMatrix;
    }

	Matrix4 Matrix4::createRotation(GLfloat x, GLfloat y, GLfloat z, GLfloat angle)
	{
		Matrix4 rotateMatrix;
		GLfloat div = sqrt(x*x+y*y+z*z);
		if( div != 0 )
		{
			x /= div;
			y /= div;
			z /= div;

			GLfloat c = cos(angle);
			GLfloat cc = 1.0f-c;
			GLfloat s = sin(angle);
			GLfloat xx = x*x;
			GLfloat yy = y*y;
			GLfloat zz = z*z;
			GLfloat xy = x*y;
			GLfloat xz = x*z;
			GLfloat yz = y*z;

			rotateMatrix.m_Matrix[0] = xx+(1.0f-xx)*c;
			rotateMatrix.m_Matrix[1] = xy*cc+z*s;
			rotateMatrix.m_Matrix[2] = xz*cc-y*s;

			rotateMatrix.m_Matrix[4] = xy*cc-z*s;
			rotateMatrix.m_Matrix[5] = yy+(1.0f-yy)*c;
			rotateMatrix.m_Matrix[6] = yz*cc+x*s;

			rotateMatrix.m_Matrix[8] = xz*cc+y*s;
			rotateMatrix.m_Matrix[9] = yz*cc-x*s;
			rotateMatrix.m_Matrix[10] = zz+(1.0f-zz)*c;

			rotateMatrix.m_Matrix[15]= 1.0f;
		}
		else
		{
			rotateMatrix.identity();
		}

		return rotateMatrix;
	}

	Matrix4 Matrix4::createTranslation(GLfloat x, GLfloat y, GLfloat z)
	{
		Matrix4 translationMatrix;
		translationMatrix.identity();
		translationMatrix.m_Matrix[12] = x;
		translationMatrix.m_Matrix[13] = y;
		translationMatrix.m_Matrix[14] = z;

		return translationMatrix;
	}

	Matrix4 Matrix4::createScale(GLfloat x, GLfloat y, GLfloat z)
	{
		Matrix4 scaleMatrix;
		scaleMatrix[0] = x;
		scaleMatrix[5] = y;
		scaleMatrix[10] = z;
		scaleMatrix[15] = 1.0f;

		return scaleMatrix;
	}
}
