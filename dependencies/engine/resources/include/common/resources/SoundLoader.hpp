#pragma once
#include <memory>
#include <string>

namespace Engine
{
	class SoundLoaderImpl;
    struct Sound;

	class SoundLoader
	{
	public:
		SoundLoader();
		~SoundLoader();

		Sound loadSound(const std::string& fileName);

	private:
		std::unique_ptr<SoundLoaderImpl> mImpl;
	};
}
