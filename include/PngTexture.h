#ifndef PNGTEXTURE_H
#define PNGTEXTURE_H

#include <Texture.h>
#include <png.h>

class PngTexture : public Texture
{
	public:
		bool load(const char* filename);
	protected:
	private:
		static void ReadProc(png_struct * def, png_byte *data, png_size_t size);
};

#endif // PNGTEXTURE_H
