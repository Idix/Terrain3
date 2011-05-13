#ifndef EARTHMATERIAL_H
#define EARTHMATERIAL_H

#include "project.h"
#include <Material.h>
#include "TextShader.h"
#include "PngTexture.h"
#include "Math/Vector3D.h"

class EarthMaterial : public Material
{
	public:
		EarthMaterial();
		void setLightPosition(GLfloat x, GLfloat y, GLfloat z);
		inline void setLightPosition(const Math::Vector3D& lightPos) { setLightPosition(lightPos[0], lightPos[1], lightPos[2]); };
		virtual void recompileShader();
	protected:
	private:
};

#endif // EARTHMATERIAL_H
