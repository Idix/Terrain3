#ifndef POSTMATERIAL_H
#define POSTMATERIAL_H

#include <Material.h>
#include <RenderTexture.h>


class PostMaterial : public Material
{
    public:
        PostMaterial(int width, int height);
        virtual ~PostMaterial();

        const Texture* getRenderTexture(){ return m_RenderTexture; };
    protected:
    private:
        RenderTexture* m_RenderTexture;
};

#endif // POSTMATERIAL_H
