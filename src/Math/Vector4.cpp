#include "Math/Vector4.h"

#include <string.h>
#include <math.h>

namespace Math {
	Vector4::Vector4(GLdouble x, GLdouble y, GLdouble z, GLdouble w) : x(m_Vector[0]), y(m_Vector[1]), z(m_Vector[2]), w(m_Vector[3])
	{
		m_Vector[0] = x;
		m_Vector[1] = y;
		m_Vector[2] = z;
		m_Vector[3] = w;
	}

	Vector4::Vector4(void) : x(m_Vector[0]), y(m_Vector[1]), z(m_Vector[2]), w(m_Vector[3])
	{
		memset(m_Vector, 0, sizeof(double)*4);
	}

	void Vector4::normalize()
	{
		GLdouble div = sqrt(x*x+y*y+z*z+w*w);
        if( div != 0 )
        {
            x /= div;
            y /= div;
            z /= div;
            w /= div;
        }
	}

	Vector4& Vector4::set(const Vector4& other)
	{
		if (this != &other)
			memcpy(m_Vector, other.m_Vector, sizeof(GLdouble)*4);
		return *this;
	}
}
