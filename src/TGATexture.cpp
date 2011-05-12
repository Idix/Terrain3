#include "TGATexture.h"

bool TGATexture::load(const char* filename)
{
    bool result = false;
    if (glfwReadImage(filename, &image, 0)) {
        result = Texture::load(true);
        glfwFreeImage(&image);
    }
    return result;
}
