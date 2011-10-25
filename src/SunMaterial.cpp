#include "SunMaterial.h"

SunMaterial::SunMaterial()
{
    m_Shader = new TextShader("shaders/sun");
    m_Shader->compile();
}
