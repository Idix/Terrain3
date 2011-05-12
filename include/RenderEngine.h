#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include "project.h"

#include "Renderable.h"
#include "Sphere.h"
#include "Camera.h"
#include "MatrixStack.h"
#include "EarthMaterial.h"
#include "CloudsMaterial.h"

class RenderEngine
{
    public:
        RenderEngine();
        ~RenderEngine();
        void render(double elapsed);
        Camera& getCamera();
        void recompileShaders();
    protected:
    private:
        Renderable* m_Renderable;
        Camera m_Camera;
        MatrixStack m_MatrixStack;
        EarthMaterial* m_EarthMaterial;
        CloudsMaterial* m_CloudsMaterial;
};

#endif // RENDERENGINE_H
