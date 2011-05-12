#include "Math/Quaternion.h"

namespace Math {
    Quaternion::Quaternion(void)
    : x(quaternion[0]), y(quaternion[1]), z(quaternion[2]), w(quaternion[3])
    {
    }

    Quaternion::Quaternion(GLdouble _x, GLdouble _y, GLdouble _z, GLdouble _w)
    : x(quaternion[0]), y(quaternion[1]), z(quaternion[2]), w(quaternion[3])
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    Quaternion::Quaternion(const Quaternion& quat)
    : x(quaternion[0]), y(quaternion[1]), z(quaternion[2]), w(quaternion[3])
    {
        for(int i=0; i<4; ++i)
            quaternion[i] = quat.quaternion[i];
    }

    Quaternion::Quaternion(GLdouble tab[4])
    : x(quaternion[0]), y(quaternion[1]), z(quaternion[2]), w(quaternion[3])
    {
        for(int i=0; i<4; ++i)
            quaternion[i] = tab[i];
    }

    Quaternion::~Quaternion(void)
    {
    }

    void Quaternion::conjugate(void)
    {
        for(int i=1; i<4; ++i)
            quaternion[i] *= -1;
    }

    Quaternion Quaternion::operator*(const Quaternion& otherQuat) const
    {
        Quaternion res;
        res.x = x*otherQuat.x - y*otherQuat.y - z*otherQuat.z - w*otherQuat.w;
        res.y = x*otherQuat.y + y*otherQuat.x + z*otherQuat.w - w*otherQuat.z;
        res.z = x*otherQuat.z - y*otherQuat.w + z*otherQuat.x + w*otherQuat.y;
        res.w = x*otherQuat.w + y*otherQuat.z - z*otherQuat.y + w*otherQuat.x;
        return res;
    }

    GLdouble Quaternion::operator[](int n) const
    {
        return quaternion[n];
    }
}
