#pragma once

#include "project.h"

namespace Math {
    class Quaternion
    {
    private:
        GLdouble quaternion[4];
        GLdouble &x;
        GLdouble &y;
        GLdouble &z;
        GLdouble &w;
    public:
        Quaternion(void);
        Quaternion(const Quaternion& quat);
        Quaternion(GLdouble _x, GLdouble _y, GLdouble _z, GLdouble _w);
        Quaternion(GLdouble tab[3]);
        ~Quaternion(void);
        void conjugate(void);
        Quaternion operator*(const Quaternion& otherQuat) const;
        GLdouble operator[](int n) const;
    };
}
