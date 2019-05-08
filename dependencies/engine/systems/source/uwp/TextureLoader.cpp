#include "textures/TextureLoader.h"
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Graphics.Imaging.h>
#include <winrt/Windows.ApplicationModel.h>
#include <memory>
#include <algorithm>
#include "IDispatcherWrapper.h"
#include "IOC.hpp"
#include "GLHelper.h"
#include "filesystem/FileSystem.h"
#include "File.h"
#include "textures/Texture2D.h"

using namespace std;
using namespace winrt;
using namespace Windows::Storage;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel;
using namespace Windows::Graphics::Imaging;
using namespace Engine;
using namespace Utilities;

namespace Engine {
	class TextureLoaderImpl
	{
	private:
		IAsyncOperation<PixelDataProvider> GetPixelDataFromImageAsync(std::shared_ptr<File> file, int& width, int& height) {
			auto stream = co_await file->Get().OpenAsync(FileAccessMode::Read);
			auto decoder = co_await BitmapDecoder::CreateAsync(stream);
			auto bitmap = co_await decoder.GetSoftwareBitmapAsync();
			width = bitmap.PixelWidth();
			height = bitmap.PixelHeight();
			auto pixelData = co_await decoder.GetPixelDataAsync(BitmapPixelFormat::Rgba8, BitmapAlphaMode::Straight, BitmapTransform(), ExifOrientationMode::IgnoreExifOrientation, ColorManagementMode::DoNotColorManage);
			co_return pixelData;
		}

		vector<GLubyte> GetPixelsFromPixelDataProvider(const PixelDataProvider& pixelDataProvider) {
			auto dpPixels = pixelDataProvider.DetachPixelData();
			auto size = dpPixels.size();
			std::vector<GLubyte> vPixels(dpPixels.begin(), dpPixels.end());
			return vPixels;
		}

	public:
		TextureLoaderImpl()
		{
			mDispatcher = IOCContainer::Instance().Resolve<IDispatcherWrapper>();
			mFileSystem = IOCContainer::Instance().Resolve<IFileSystem>();
		}	

		void LoadTexture(Texture2D& texture) 
		{
			if (texture.Name != EMPTY_TEXTURE_NAME) {
				auto file = mFileSystem->LoadFile(std::wstring(L"\\textures\\" + texture.Name));
				if (file) {
					int width, height;
					auto pixelData = GetPixelDataFromImageAsync(file, width, height).get();

					texture.Width = width;
					texture.Height = height;

					auto dpPixels = GetPixelsFromPixelDataProvider(pixelData);
					mDispatcher->ScheduleOnGameThread([&, dpPixels, texture]() {
						auto size = dpPixels.size();
						int width = static_cast<int>(texture.Width) * 4;
						int height = static_cast<int>(texture.Height);
						GLubyte* pixels = (GLubyte*)malloc(size);
						for (int i = 0; i < texture.Height; i++) {
							// note that png is ordered top to
							// bottom, but OpenGL expect it bottom to top
							// so the order or swapped
							auto destination = pixels + (width * (height - 1 - i));
							auto source = &dpPixels[i*width];
							memcpy(destination, source, width);
						}
						SetTexturePixels(texture.TextureIndex, texture.Width, texture.Height, pixels);
						delete[] pixels;
					});
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
		std::shared_ptr<IDispatcherWrapper> mDispatcher;
		std::shared_ptr<IFileSystem> mFileSystem;
	};
}

TextureLoader::TextureLoader()
	: mImpl(std::make_unique<TextureLoaderImpl>())
{

}

TextureLoader::~TextureLoader()
{
	mImpl.reset(nullptr);
}

void TextureLoader::LoadTexture(Texture2D& texture)
{
	mImpl->LoadTexture(texture);
}
