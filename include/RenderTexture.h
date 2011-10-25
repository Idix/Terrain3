#ifndef RENDERTEXTURE_H
#define RENDERTEXTURE_H

#include <Texture.h>


class RenderTexture : public Texture
{
    public:
        RenderTexture(int width, int height);
        void resize(int width, int height);
    protected:
    private:
};

#endif // RENDERTEXTURE_H
