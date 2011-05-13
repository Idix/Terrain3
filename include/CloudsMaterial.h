#ifndef CLOUDSMATERIAL_H
#define CLOUDSMATERIAL_H

#include "project.h"
#include <Material.h>
#include "PngTexture.h"
#include "TextShader.h"
#include "Math/Vector3D.h"

class CloudsMaterial : public Material
{
	public:
		CloudsMaterial();
		void setLightPosition(GLfloat x, GLfloat y, GLfloat z);
		inline void setLightPosition(const Math::Vector3D& lightPos) { setLightPosition(lightPos.getX(), lightPos.getY(), lightPos.getZ()); };
	protected:
	private:
};

#endif // CLOUDSMATERIAL_H
