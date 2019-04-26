#include "textures/TextureManager.h"
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Graphics.Imaging.h>
#include <winrt/Windows.ApplicationModel.h>
#include <memory>
#include "DispatcherWrapper.h"
#include "IOC.hpp"
#include "GLHelper.h"

using namespace std;
using namespace winrt;
using namespace Windows::Storage;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel;
using namespace Windows::Graphics::Imaging;
using namespace Engine;
using namespace Utilities;

namespace Engine {
	class TextureManagerImpl
	{
	private:
		IAsyncOperation<IStorageFile> LoadImageAsync(const wstring& filename) {
			auto folder = Package::Current().InstalledLocation();
			auto path = folder.Path().c_str();
			auto file = co_await folder.TryGetItemAsync(filename);
			co_return file.as<IStorageFile>();
		}

		IAsyncOperation<PixelDataProvider> GetPixelDataFromImageAsync(IStorageFile file, int& width, int& height) {
			auto stream = co_await file.OpenAsync(FileAccessMode::Read);
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
		TextureManagerImpl()
		{
			mDispatcher = IOCContainer::Instance().Resolve<DispatcherWrapper>();
		}	

		void LoadTexture(Texture2D& texture) {
			if (texture.Name != EMPTY_TEXTURE_NAME) {
				int width, height;
				GLuint textureId = texture.TextureIndex;
				auto file = LoadImageAsync(texture.Name).get();
				if (file) {
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
						SetTexturePixels(texture, pixels);
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

		Texture2D CreateEmptyTexture() {
			Texture2D texture;
			texture.TextureIndex = GenerateTexture();
			texture.Width = 1;
			texture.Height = 1;
			texture.Name = EMPTY_TEXTURE_NAME;

			auto pixels = new GLubyte[4]{ 255, 0, 255 , 255 };
			SetTexturePixels(texture, pixels);
			delete[] pixels;

			return texture;
		}

	private:
		HANDLE mSyncAsyncEvent = nullptr;
		std::shared_ptr<DispatcherWrapper> mDispatcher;
	};
}

TextureManager::TextureManager()
	: mInitialized(false)
	, mImpl(new Engine::TextureManagerImpl())
{

}

TextureManager::~TextureManager()
{
	delete(mImpl);
}

void TextureManager::LoadTextures(vector<wstring> filenames)
{
	if (!mInitialized) {
		auto emptyTexture = mImpl->CreateEmptyTexture();
		mTextures[emptyTexture.Name] = emptyTexture;
	}

	for (auto const& filename : filenames)
	{
		Texture2D texture;
		texture.Name = filename;
		texture.TextureIndex = GenerateTexture();
		mTextures[filename] = texture;
	}

	for (auto& texture : mTextures)
	{
		mImpl->LoadTexture(texture.second);
	}

	mInitialized = true;
}

Texture2D TextureManager::GetTexture(wstring filename) const
{
	if (mTextures.count(filename) == 1) {
		auto texture = mTextures.at(filename);
		if (texture.Name == filename) {
			return texture;
		}
	}
	return mTextures.at(EMPTY_TEXTURE_NAME);
}