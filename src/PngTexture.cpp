#include "PngTexture.h"

#include <fstream>

bool PngTexture::load(const char* filename)
{
    png_byte magic[8];
    GLuint i;

    /* Open image file */
    std::ifstream is(filename, std::ifstream::in);
    if (is.fail())
    {
    	std::cerr << "error: couldn't open \"" << filename << "\"!" << std::endl;
        return false;
    }

    /* Read magic number */
    is.read((char*)magic, sizeof(magic));

    /* Check for valid magic number */
    if (!png_check_sig (magic, sizeof (magic)))
    {
    	std::cerr << "error: \"" << filename << "\" is not a valid PNG image!" << std::endl;
        return false;
    }

    /* Create a png read struct */
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr)
        return false;

    /* Create a png info struct */
    png_infop info_ptr = png_create_info_struct (png_ptr);
    if (!info_ptr)
    {
        png_destroy_read_struct (&png_ptr, NULL, NULL);
        return false;
    }

    /* Initialize the setjmp for returning properly after a libpng
    error occured */
    if (setjmp (png_jmpbuf (png_ptr)))
    {
        png_destroy_read_struct (&png_ptr, &info_ptr, NULL);
        return false;
    }

    /* Tell libpng that we have already read the magic number */
    png_set_sig_bytes(png_ptr, sizeof (magic));

	png_set_read_fn(png_ptr, &is, PngTexture::ReadProc);

    /* Read png info */
    png_read_info (png_ptr, info_ptr);

    int bit_depth, color_type;

    /* Get some usefull information from header */
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);

    /* Convert index color images to RGB images */
    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb (png_ptr);

    /* Convert 1-2-4 bits grayscale images to 8 bits
    grayscale. */
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_gray_1_2_4_to_8 (png_ptr);

    if (png_get_valid (png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha (png_ptr);

    if (bit_depth == 16)
        png_set_strip_16 (png_ptr);
    else if (bit_depth < 8)
        png_set_packing (png_ptr);

    /* Update info structure to apply transformations */
    png_read_update_info (png_ptr, info_ptr);

    /* Retrieve updated information */
    png_uint_32 w, h;

    png_get_IHDR (png_ptr, info_ptr, &w, &h, &bit_depth,
                  &color_type, NULL, NULL, NULL);
    image.Width = w;
    image.Height = h;

    switch (color_type)
    {
        case PNG_COLOR_TYPE_GRAY:
            image.Format = GL_RED;
            image.BytesPerPixel = 1;
            break;

        case PNG_COLOR_TYPE_GRAY_ALPHA:
            image.Format = GL_RG;
            image.BytesPerPixel = 2;
            break;

        case PNG_COLOR_TYPE_RGB:
            image.Format = GL_RGB;
            image.BytesPerPixel = 3;
            break;

        case PNG_COLOR_TYPE_RGB_ALPHA:
            image.Format = GL_RGBA;
            image.BytesPerPixel = 4;
            break;

        default:
            /* Badness */
            break;
    }

    /* We can now allocate memory for storing pixel data */
	image.Data = new unsigned char[w * h * image.BytesPerPixel];

    png_bytep *row_pointers;

    /* Setup a pointer array.  Each one points at the begening of a row. */
	row_pointers = new png_bytep[h];

    for (i = 0; i < h; ++i)
    {
        row_pointers[i] = (png_bytep)(image.Data + ((h - (i + 1)) * w * image.BytesPerPixel));
    }

    /* Read pixel data using row pointers */
    png_read_image (png_ptr, row_pointers);

    /* We don't need row pointers anymore */
	delete [] row_pointers;

    /* Finish decompression and release memory */
    png_read_end (png_ptr, NULL);
    png_destroy_read_struct (&png_ptr, &info_ptr, NULL);

	return Texture::load();
}

void PngTexture::ReadProc(png_struct * def, png_byte *data, png_size_t size)
{
	std::ifstream* is = (std::ifstream*) png_get_io_ptr(def);
	is->read((char*)data, size);
}
