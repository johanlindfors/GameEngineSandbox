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

#define EMPTY_TEXTURE_NAME L"empty"

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

	fire_and_forget LoadTextureAsync(Texture2D& texture) {
		int width, height;
		GLuint textureId = texture.TextureIndex;
		// Load file
		auto file = co_await LoadImageAsync(texture.Name);
		if (file) {
			// Get PixelDataProvider
			auto pixelData = co_await GetPixelDataFromImageAsync(file, width, height);

			texture.Width = static_cast<float>(width);
			texture.Height = static_cast<float>(height);

			co_await mDispatcher->RunAsync([&]() {
				// Get Pixels
				auto dpPixels = GetPixelsFromPixelDataProvider(pixelData);
				auto size = dpPixels.size();

				auto pixels = new GLubyte[size];
				memcpy(pixels, &(dpPixels[0]), size);
				SetTexturePixels(textureId, width, height, pixels);
				delete[] pixels;
				SetEvent(mSyncAsyncEvent);
			});
		}
		else {
			DeleteTexture(texture.TextureIndex);
			texture.TextureIndex = 0;
			texture.Width = 0;
			texture.Height = 0;
			texture.Name = L"";
			SetEvent(mSyncAsyncEvent);
		}
	}

public:
	TextureManagerImpl() 
	{
		mDispatcher = IOCContainer::Instance().Resolve<DispatcherWrapper>();
	}

	void LoadTexture(Texture2D& texture)
	{
		if (texture.Name != EMPTY_TEXTURE_NAME) {
			mSyncAsyncEvent = CreateEvent(nullptr, true, true, L"LoadTextureEvent");
			ResetEvent(mSyncAsyncEvent);

			LoadTextureAsync(texture);

			WaitForSingleObject(mSyncAsyncEvent, INFINITE);
			CloseHandle(mSyncAsyncEvent);
			mSyncAsyncEvent = nullptr;
		}
	}

	Texture2D CreateEmptyTexture() {
		Texture2D texture;
		texture.TextureIndex = GenerateTexture();
		texture.Width = 1;
		texture.Height = 1;
		texture.Name = EMPTY_TEXTURE_NAME;
		
		mSyncAsyncEvent = CreateEvent(nullptr, true, true, L"LoadTextureEvent");
		ResetEvent(mSyncAsyncEvent);

		mDispatcher->RunAsync([&,texture]() {
			auto pixels = new GLubyte[4]{ 255, 0, 255 , 0 };
			SetTexturePixels(texture.TextureIndex, texture.Width, texture.Height, pixels);
			delete[] pixels;
			SetEvent(mSyncAsyncEvent);
		});

		WaitForSingleObject(mSyncAsyncEvent, INFINITE);
		CloseHandle(mSyncAsyncEvent);
		mSyncAsyncEvent = nullptr;

		return texture;
	}

private:
	HANDLE mSyncAsyncEvent = nullptr;
	std::shared_ptr<DispatcherWrapper> mDispatcher;
};

TextureManager::TextureManager() 
    : mInitialized(false)
    , mImpl(new TextureManagerImpl())
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

	for (auto &texture : mTextures)
	{
		mImpl->LoadTexture(texture.second);
	}

	mInitialized = true;
}

Texture2D TextureManager::GetTexture(wstring filename) const 
{
    if(mTextures.count(filename) == 1) {
		auto texture = mTextures.at(filename);
		if (texture.Name == filename) {
			return texture;
		}
	}
	return mTextures.at(EMPTY_TEXTURE_NAME);
}