#ifndef MATERIAL_H
#define MATERIAL_H

#include "project.h"
#include "Texture.h"
#include "Shader.h"
#include "Math/Matrix4.h"

class Material
{
	public:
		Material();
		virtual ~Material();
		virtual void bind();
		virtual void recompileShader();
		virtual void setMvpMatrix(const GLfloat* matrix);
		inline void setMvpMatrix(const Math::Matrix4& matrix) { setMvpMatrix(matrix.getRaw()); };
		virtual void setMvMatrix(const GLfloat* matrix);
		inline void setMvMatrix(const Math::Matrix4& matrix) { setMvMatrix(matrix.getRaw()); };
		virtual void setNormalMatrix(const GLfloat* matrix);
	protected:
		Shader* m_Shader;
		GLint m_MaxTextureCount;
		bool appendTexture(const char* textureName, const Texture* textureObject);
	private:
		int m_TextureCount;
		const Texture** m_TextureList;
		const char** m_TextureName;
};

#endif // MATERIAL_H
