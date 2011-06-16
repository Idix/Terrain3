#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include "project.h"

#include "Renderable.h"
#include "Sphere.h"
#include "Tube.h"
#include "RetroMaterial.h"
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
        Tube* m_Tubes[3];
        Camera m_Camera;
        MatrixStack m_MatrixStack;
        EarthMaterial* m_EarthMaterial;
        CloudsMaterial* m_CloudsMaterial;
        RetroMaterial* m_RetroMaterial;
};

#endif // RENDERENGINE_H
