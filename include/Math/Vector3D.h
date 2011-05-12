#pragma once

#include "project.h"

namespace Math
{
    class Vector3D
    {
    private:
        GLdouble vector[3];
        GLdouble &x;
        GLdouble &y;
        GLdouble &z;
    public:
        Vector3D(void);
        Vector3D(const Vector3D& vec);
        Vector3D(GLdouble _x, GLdouble _y, GLdouble _z);
        Vector3D(GLdouble tab[3]);
        Vector3D cross(const Vector3D& otherVector) const;
        GLdouble dot(const Vector3D& otherVector) const;
        void normalize(void);
        void setZero(void);
        GLdouble getDist(void) const;
        Vector3D& operator+=(const Vector3D& vec);
        Vector3D& operator-=(const Vector3D& vec);
        Vector3D operator+(const Vector3D& vec) const;
        Vector3D operator-(const Vector3D& vec) const;
        GLdouble operator[](int n) const;
        Vector3D& operator=(const Vector3D& vec);
        Vector3D operator*(double scalar) const;
        const GLdouble* getVector();
        void set(const Vector3D& vec);
        void set(GLdouble _x, GLdouble _y, GLdouble _z);
        void setX(GLdouble _x);
        void setY(GLdouble _y);
        void setZ(GLdouble _z);
        GLdouble getX(void) const;
        GLdouble getY(void) const;
        GLdouble getZ(void) const;
    };
}
