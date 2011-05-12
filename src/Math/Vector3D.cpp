#include "Math/Vector3D.h"
#include <math.h>

namespace Math
{
    Vector3D::Vector3D(void) : x(vector[0]), y(vector[1]), z(vector[2])
    {
    }

    Vector3D::Vector3D(GLdouble _x, GLdouble _y, GLdouble _z) : x(vector[0]), y(vector[1]), z(vector[2])
    {
        x = _x;
        y = _y;
        z = _z;
    }

    Vector3D::Vector3D(const Vector3D& vec) : x(vector[0]), y(vector[1]), z(vector[2])
    {
        set(vec);
    }

    Vector3D::Vector3D(GLdouble tab[3]) : x(vector[0]), y(vector[1]), z(vector[2])
    {
        for(int i=0; i<3; ++i)
            vector[i] = tab[i];
    }

    Vector3D Vector3D::cross(const Vector3D& otherVector) const
    {
        Vector3D res;
        res.x = y * otherVector.z - z * otherVector.y;
        res.y = z * otherVector.x - x * otherVector.z;
        res.z = x * otherVector.y - y * otherVector.x;
        return res;
    }

    void Vector3D::normalize(void)
    {
        GLdouble div = sqrt(x*x+y*y+z*z);
        if( div != 0 )
        {
            x /= div;
            y /= div;
            z /= div;
        }
    }

    void Vector3D::setZero(void)
    {
        for(int i=0; i<3; ++i)
            vector[i] = 0.0;
    }

    GLdouble Vector3D::getDist(void) const
    {
        return sqrt(x*x+y*y+z*z);
    }

    GLdouble Vector3D::dot(const Vector3D& otherVector) const
    {
        return x*otherVector.x + y*otherVector.y + z*otherVector.z;
    }

    const GLdouble* Vector3D::getVector()
    {
        return vector;
    }

    Vector3D& Vector3D::operator+=(const Vector3D& vec)
    {
        for(int i=0; i<3; ++i)
            vector[i] += vec.vector[i];
        return *this;
    }

    Vector3D& Vector3D::operator-=(const Vector3D& vec)
    {
        for(int i=0; i<3; ++i)
            vector[i] -= vec.vector[i];
        return *this;
    }

    Vector3D Vector3D::operator+(const Vector3D& vec) const
    {
        Vector3D res(*this);
        res += vec;
        return res;
    }

    Vector3D Vector3D::operator-(const Vector3D& vec) const
    {
        Vector3D res(*this);
        res -= vec;
        return res;
    }

    GLdouble Vector3D::operator[](int n) const
    {
        return vector[n];
    }

    Vector3D& Vector3D::operator=(const Vector3D& vec)
    {
        if( &vec != this )
        {
            for(int i=0; i<3; ++i)
                vector[i] = vec.vector[i];
        }
        return *this;
    }

    Vector3D Vector3D::operator*(double scalar) const
    {
        Vector3D result(*this);
        result.x *= scalar;
        result.y *= scalar;
        result.z *= scalar;

        return result;
    }

    void Vector3D::set(const Vector3D& vec)
    {
        for(int i=0; i<3; ++i)
            vector[i] = vec.vector[i];
    }

    void Vector3D::set(GLdouble _x, GLdouble _y, GLdouble _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    void Vector3D::setX(GLdouble _x)
    {
        x = _x;
    }

    void Vector3D::setY(GLdouble _y)
    {
        y = _y;
    }

    void Vector3D::setZ(GLdouble _z)
    {
        z = _z;
    }

    GLdouble Vector3D::getX() const
    {
        return x;
    }

    GLdouble Vector3D::getY() const
    {
        return y;
    }

    GLdouble Vector3D::getZ() const
    {
        return z;
    }
}
