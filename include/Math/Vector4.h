#ifndef VECTOR4_H
#define VECTOR4_H

#include "project.h"
#include "Math/Vector3D.h"

namespace Math {
	class Vector4
	{
		public:
			Vector4(void);
			Vector4(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
			Vector4(const Vector4& other);
			Vector4& set(const Vector4& other);
			inline Vector4& operator=(const Vector4& other) { return set(other); };
			inline Vector3D extractVector3() const { return Vector3D(x, y, z); };
			inline GLdouble operator[](unsigned int n) const { return m_Vector[n]; };
			void normalize();
		protected:
		private:
			GLdouble m_Vector[4];
			GLdouble& x;
			GLdouble& y;
			GLdouble& z;
			GLdouble& w;
	};
}
#endif // VECTOR4_H
