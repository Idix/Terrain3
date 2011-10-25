#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include "project.h"

#include "Renderable.h"
#include "Sphere.h"
#include "Quad.h"
#include "Camera.h"
#include "MatrixStack.h"
#include "EarthMaterial.h"
#include "CloudsMaterial.h"
#include "PostMaterial.h"
#include "SunMaterial.h"
#include "Framebuffer.h"
#include "RenderTexture.h"

class RenderEngine
{
    public:
        RenderEngine(int width, int height);
        ~RenderEngine();
        void render(double elapsed);
        Camera& getCamera();
        void recompileShaders();
        void resize(int width, int height);
    protected:
        virtual void pass1(double elapsed);
        virtual void pass2(double elapsed);
    private:
        Renderable* m_Renderable;
        Quad* m_PostQuad;
        Sphere* m_Sun;
        Camera m_Camera;
        MatrixStack m_MatrixStack;
        EarthMaterial* m_EarthMaterial;
        CloudsMaterial* m_CloudsMaterial;
        SunMaterial* m_SunMaterial;
        PostMaterial* m_PostMaterial;
        Framebuffer* m_Framebuffer;
};

#endif // RENDERENGINE_H
