#include "resources/TextureLoader.h"
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Graphics.Imaging.h>
#include <winrt/Windows.ApplicationModel.h>
#include <memory>
#include "IDispatcherWrapper.h"
#include "utilities/IOC.hpp"
#include "utilities/GLHelper.h"
#include "filesystem/FileSystem.h"
#include "File.h"
#include "resources/Texture2D.h"

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
		static IAsyncOperation<PixelDataProvider> GetPixelDataFromImageAsync(std::shared_ptr<File> file, int& width, int& height) {
			const auto stream = co_await file->Get().OpenAsync(FileAccessMode::Read);
			const auto decoder = co_await BitmapDecoder::CreateAsync(stream);
			const auto bitmap = co_await decoder.GetSoftwareBitmapAsync();
			width = bitmap.PixelWidth();
			height = bitmap.PixelHeight();
			auto pixelData = co_await decoder.GetPixelDataAsync(BitmapPixelFormat::Rgba8, BitmapAlphaMode::Straight, BitmapTransform(), ExifOrientationMode::IgnoreExifOrientation, ColorManagementMode::DoNotColorManage);
			co_return pixelData;
		}

		static vector<GLubyte> GetPixelsFromPixelDataProvider(const PixelDataProvider& pixelDataProvider) {
			auto dpPixels = pixelDataProvider.DetachPixelData();
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
				const auto file = mFileSystem->LoadFile(std::string(L"\\textures\\" + texture.Name));
				if (file) {
					int width, height;
					const auto pixelData = GetPixelDataFromImageAsync(file, width, height).get();

					texture.Width = width;
					texture.Height = height;

					auto dpPixels = GetPixelsFromPixelDataProvider(pixelData);
					mDispatcher->ScheduleOnGameThread([&, dpPixels, texture]() {
						const auto size = dpPixels.size();
						const auto textureWidth = texture.Width * 4;
						const auto textureHeight = texture.Height;
						const auto pixels = static_cast<GLubyte*>(malloc(size));
						for (auto i = 0; i < texture.Height; i++) {
							// note that png is ordered top to
							// bottom, but OpenGL expect it bottom to top
							// so the order or swapped
							const auto destination = pixels + textureWidth * (textureHeight - 1 - i);
							const auto source = &dpPixels[i * textureWidth];
							memcpy(destination, source, textureWidth);
						}
						bool hasAlpha = true;
						SetTexturePixels(texture.TextureIndex, texture.Width, texture.Height, hasAlpha, pixels);
						free(pixels);
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
	: mImpl(std::make_unique<TextureLoaderImpl>()) { }

TextureLoader::~TextureLoader()
{
	mImpl.reset(nullptr);
}

void TextureLoader::LoadTexture(Texture2D& texture)
{
	mImpl->LoadTexture(texture);
}
