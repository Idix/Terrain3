#include "Math/Rotation.h"
#include "Math/Quaternion.h"
#include <math.h>

namespace Math
{
    Rotation::Rotation(const Vector3D& _axis, GLdouble _angle) : axis(_axis), angle(-_angle)
    {
    }

    Rotation::~Rotation(void)
    {
    }

    Vector3D Rotation::rotate(const Vector3D& vector) const
    {
        Quaternion q1(
            cos(angle*0.5),
            axis[0]*sin(angle*0.5),
            axis[1]*sin(angle*0.5),
            axis[2]*sin(angle*0.5)); // Partie gauche de la rotation avec des quaternion
        Quaternion q2(0.0, vector[0], vector[1], vector[2]); // Le quaternion qui va prendre la position initial
        Quaternion q3(q1); // Partie droite
        q3.conjugate();

        Quaternion res = q1*q2*q3;
        return Vector3D(res[1], res[2], res[3]);
    }
}
