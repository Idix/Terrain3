#ifndef TGATEXTURE_H
#define TGATEXTURE_H

#include "project.h"
#include <Texture.h>

class TGATexture : public Texture
{
    public:
        bool load(const char* filename);
    protected:
    private:
};

#endif // TGATEXTURE_H
