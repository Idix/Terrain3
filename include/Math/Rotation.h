#pragma once

#include "project.h"
#include "Vector3D.h"

namespace Math
{
    class Rotation
    {
    private:
        Vector3D axis;
        GLdouble angle;
    public:
        Rotation(const Vector3D& _axis, GLdouble _angle);
        ~Rotation(void);
        Vector3D rotate(const Vector3D& vector) const;
    };
}
