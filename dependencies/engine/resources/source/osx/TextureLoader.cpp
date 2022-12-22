#include "resources/TextureLoader.h"
#include "filesystem/FileSystem.h"
#include "utilities/GLHelper.h"
#include "png.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "utilities/IOC.hpp"
#include "File.h"
#include "resources/Texture2D.h"

using namespace std;
using namespace Engine;
using Utilities::IOCContainer;

namespace Engine {
	class TextureLoaderImpl {
	private:
		static bool loadPngImage(std::shared_ptr<File> file, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData) {
			png_structp png_ptr;
			png_infop info_ptr;
			const unsigned int sig_read = 0;
			int color_type, interlace_type;
			FILE *fp;

			if(file->IsOpen()) {
				fp = file->Get();
			} else {
				return false;
			}

			/* Create and initialize the png_struct
			* with the desired error handler
			* functions.  If you want to use the
			* default stderr and longjump method,
			* you can supply NULL for the last
			* three parameters.  We also supply the
			* the compiler header file version, so
			* that we know if the application
			* was compiled with a compatible version
			* of the library.  REQUIRED
			*/
			png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
				nullptr, nullptr, nullptr);

			if (png_ptr == nullptr) {
				fclose(fp);
				return false;
			}

			/* Allocate/initialize the memory
			* for image information.  REQUIRED. */
			info_ptr = png_create_info_struct(png_ptr);
			if (info_ptr == nullptr) {
				fclose(fp);
				png_destroy_read_struct(&png_ptr, nullptr, nullptr);
				return false;
			}

			/* Set error handling if you are
			* using the setjmp/longjmp method
			* (this is the normal method of
			* doing things with libpng).
			* REQUIRED unless you  set up
			* your own error handlers in
			* the png_create_read_struct()
			* earlier.
			*/
			if (setjmp(png_jmpbuf(png_ptr))) {
				/* Free all of the memory associated
				* with the png_ptr and info_ptr */
				png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
				fclose(fp);
				/* If we get here, we had a
				* problem reading the file */
				return false;
			}

			/* Set up the output control if
			* you are using standard C streams */
			png_init_io(png_ptr, fp);

			/* If we have already
			* read some of the signature */
			png_set_sig_bytes(png_ptr, sig_read);

			/*
			* If you have enough memory to read
			* in the entire image at once, and
			* you need to specify only
			* transforms that can be controlled
			* with one of the PNG_TRANSFORM_*
			* bits (this presently excludes
			* dithering, filling, setting
			* background, and doing gamma
			* adjustment), then you can read the
			* entire image (including pixels)
			* into the info structure with this
			* call
			*
			* PNG_TRANSFORM_STRIP_16 |
			* PNG_TRANSFORM_PACKING  forces 8 bit
			* PNG_TRANSFORM_EXPAND forces to
			*  expand a palette into RGB
			*/
			png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, nullptr);

			png_uint_32 width, height;
			int bit_depth;
			png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
				&interlace_type, nullptr, nullptr);
			outWidth = width;
			outHeight = height;

			outHasAlpha = color_type & PNG_COLOR_MASK_ALPHA;
			const auto row_bytes = static_cast<unsigned int>(png_get_rowbytes(png_ptr, info_ptr));
			*outData = static_cast<unsigned char*>(malloc(row_bytes * outHeight));

			const auto row_pointers = png_get_rows(png_ptr, info_ptr);

			for (auto i = 0; i < outHeight; i++) {
				// note that png is ordered top to
				// bottom, but OpenGL expect it bottom to top
				// so the order or swapped
				memcpy(*outData + (row_bytes * (outHeight - 1 - i)), row_pointers[i], row_bytes);
			}

			/* Clean up after the read,
			* and free any memory allocated */
			png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

			/* Close the file */
			fclose(fp);

			/* That's it */
			return true;
		}

	public:
		TextureLoaderImpl()
		{
			mFileSystem = IOCContainer::Instance().Resolve<IFileSystem>();
		}

		void LoadTexture(Texture2D& texture)
		{
			if (texture.Name != EMPTY_TEXTURE_NAME) {
				const auto file = mFileSystem->LoadFile(std::string(L"textures/" + texture.Name));
				if(file){
					int width, height;
					auto hasAlpha = false;
					GLubyte *textureImage;
					const auto success = loadPngImage(file, width, height, hasAlpha, &textureImage);
					if (!success) {
						std::cout << "Unable to load png file: " << std::endl;
						texture.Name = L"";
						return;
					}
					texture.Width = width;
					texture.Height = height;
					std::cout << "Image loaded " << width << " " << height << " alpha " << hasAlpha << std::endl;
					SetTexturePixels(texture.TextureIndex, texture.Width, texture.Height, hasAlpha, textureImage);
					if (textureImage) {
						delete textureImage;
					}
				}
				else {
					DeleteTexture(texture.TextureIndex);
					texture.TextureIndex = 0;
					texture.Width = 0;
					texture.Height = 0;
					texture.Name = L"";
				}
			}
		}

	private:
		std::shared_ptr<IFileSystem> mFileSystem;
	};
}

TextureLoader::TextureLoader()
	: mImpl(std::make_unique<TextureLoaderImpl>()) { }

TextureLoader::~TextureLoader()
{
	mImpl.reset(nullptr);
}

void TextureLoader::LoadTexture(Texture2D& texture)
{
	mImpl->LoadTexture(texture);
}
