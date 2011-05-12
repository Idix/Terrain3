#ifndef MATRIX4_H
#define MATRIX4_H

#include "project.h"
#include "Math/Vector4.h"
#include "Math/Vector3D.h"

namespace Math
{
    class Matrix4
    {
        public:
            Matrix4();
            inline Matrix4(const Matrix4& other) { set(other); };
            void set(const Matrix4& other);
            void set(unsigned int i, unsigned int j, GLfloat newValue);
            inline GLfloat& operator[](unsigned int index);
            void identity();
            const GLfloat* getRaw() const;
            const GLfloat* getMatrix3Raw();
            Matrix4 multiply(const Matrix4& other) const;
            Vector4 multiply(const Vector4& vector) const;
            inline Matrix4 operator*(const Matrix4& other) const { return multiply(other); };
            inline Vector4 operator*(const Vector4& vector) const { return multiply(vector); };
            Matrix4& operator*=(const Matrix4& other);

            static Matrix4 createPerspective(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far);

            static Matrix4 createRotation(GLfloat x, GLfloat y, GLfloat z, GLfloat angle);
            inline static Matrix4 createRotation(const Vector3D& axis, GLfloat angle) { return createRotation(axis[0], axis[1], axis[2], angle); };
            static Matrix4 createTranslation(GLfloat x, GLfloat y, GLfloat z);
            inline static Matrix4 createTranslation(const Vector3D& dir) { return createTranslation(dir[0], dir[1], dir[2]); };
            static Matrix4 createScale(GLfloat x, GLfloat y, GLfloat z);
        protected:
        private:
            GLfloat m_Matrix[16];
            GLfloat m_NormalMatrix[9];
    };
}

#endif // MATRIX4_H
