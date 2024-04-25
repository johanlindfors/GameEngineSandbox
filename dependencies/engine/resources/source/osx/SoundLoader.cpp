#include "resources/SoundLoader.hpp"
#include "filesystem/FileSystem.hpp"
#include "utilities/ALHelper.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include "utilities/IOC.hpp"
#include "utilities/Logger.hpp"
#include "filesystem/File.hpp"
#include "resources/Sound.hpp"

using namespace std;
using namespace Engine;
using Utilities::IOCContainer;

namespace Engine {
	class SoundLoaderImpl 
	{
	public:
		SoundLoaderImpl()
			: mFileSystem(IOCContainer::instance().resolve<IFileSystem>()) { }	

		// char* loadSound(const string& fileName)
		// {
		// 	const auto file = mFileSystem->loadFile(std::string("audio/" + fileName), false);
		//     debuglog << "[SoundLoaderImpl::LoadSound] Loading sound" << endl;
		// 	std::string sound;
		// 	if(file && file->isOpen()){
		// 		auto fileHandle = file->get();
		// 		char buffer[100];
		// 		while(!feof(fileHandle)) {
		// 			if(fgets(buffer, 100, fileHandle) != NULL)
		// 				sound += buffer;
		// 		}
		// 	}
		// 	return sound.c_str();
		// }

		std::int32_t convert_to_int(char* buffer, std::size_t len)
		{
			std::int32_t a = 0;
			int num = 1;
			if(*(char *)&num == 1)
				std::memcpy(&a, buffer, len);
			else
				for(std::size_t i = 0; i < len; ++i)
					reinterpret_cast<char*>(&a)[3 - i] = buffer[i];
			return a;
		}

		bool load_wav_file_header(std::ifstream& file,
								std::uint8_t& channels,
								std::int32_t& sampleRate,
								std::uint8_t& bitsPerSample,
								ALsizei& size)
		{
			char buffer[4];
			if(!file.is_open())
				return false;

			// the RIFF
			if(!file.read(buffer, 4))
			{
				std::cerr << "ERROR: could not read RIFF" << std::endl;
				return false;
			}
			if(std::strncmp(buffer, "RIFF", 4) != 0)
			{
				std::cerr << "ERROR: file is not a valid WAVE file (header doesn't begin with RIFF)" << std::endl;
				return false;
			}

			// the size of the file
			if(!file.read(buffer, 4))
			{
				std::cerr << "ERROR: could not read size of file" << std::endl;
				return false;
			}

			// the WAVE
			if(!file.read(buffer, 4))
			{
				std::cerr << "ERROR: could not read WAVE" << std::endl;
				return false;
			}
			if(std::strncmp(buffer, "WAVE", 4) != 0)
			{
				std::cerr << "ERROR: file is not a valid WAVE file (header doesn't contain WAVE)" << std::endl;
				return false;
			}

			// "fmt/0"
			if(!file.read(buffer, 4))
			{
				std::cerr << "ERROR: could not read fmt/0" << std::endl;
				return false;
			}

			// this is always 16, the size of the fmt data chunk
			if(!file.read(buffer, 4))
			{
				std::cerr << "ERROR: could not read the 16" << std::endl;
				return false;
			}

			// PCM should be 1?
			if(!file.read(buffer, 2))
			{
				std::cerr << "ERROR: could not read PCM" << std::endl;
				return false;
			}

			// the number of channels
			if(!file.read(buffer, 2))
			{
				std::cerr << "ERROR: could not read number of channels" << std::endl;
				return false;
			}
			channels = convert_to_int(buffer, 2);

			// sample rate
			if(!file.read(buffer, 4))
			{
				std::cerr << "ERROR: could not read sample rate" << std::endl;
				return false;
			}
			sampleRate = convert_to_int(buffer, 4);

			// (sampleRate * bitsPerSample * channels) / 8
			if(!file.read(buffer, 4))
			{
				std::cerr << "ERROR: could not read (sampleRate * bitsPerSample * channels) / 8" << std::endl;
				return false;
			}

			// ?? dafaq
			if(!file.read(buffer, 2))
			{
				std::cerr << "ERROR: could not read dafaq" << std::endl;
				return false;
			}

			// bitsPerSample
			if(!file.read(buffer, 2))
			{
				std::cerr << "ERROR: could not read bits per sample" << std::endl;
				return false;
			}
			bitsPerSample = convert_to_int(buffer, 2);

			// data chunk header "data"
			if(!file.read(buffer, 4))
			{
				std::cerr << "ERROR: could not read data chunk header" << std::endl;
				return false;
			}
			if(std::strncmp(buffer, "data", 4) != 0)
			{
				std::cerr << "ERROR: file is not a valid WAVE file (doesn't have 'data' tag)" << std::endl;
				return false;
			}

			// size of data
			if(!file.read(buffer, 4))
			{
				std::cerr << "ERROR: could not read data size" << std::endl;
				return false;
			}
			size = convert_to_int(buffer, 4);

			/* cannot be at the end of file */
			if(file.eof())
			{
				std::cerr << "ERROR: reached EOF on the file" << std::endl;
				return false;
			}
			if(file.fail())
			{
				std::cerr << "ERROR: fail state set on the file" << std::endl;
				return false;
			}

			return true;
		}

		char* load_wav(const std::string& filename,
					std::uint8_t& channels,
					std::int32_t& sampleRate,
					std::uint8_t& bitsPerSample,
					ALsizei& size)
		{
			auto assetsDirectory = mFileSystem->getAssetsDirectory();
			auto filepath = std::string(assetsDirectory + "audio/" + filename);
			debuglog << "[SoundLoaderImpl::LoadSound] Loading sound '" << filepath << "'" << endl;

			std::ifstream in(filepath, std::ios::binary);
			if(!in.is_open())
			{
				std::cerr << "ERROR: Could not open \"" << filepath << "\"" << std::endl;
				return nullptr;
			}
			if(!load_wav_file_header(in, channels, sampleRate, bitsPerSample, size))
			{
				std::cerr << "ERROR: Could not load wav header of \"" << filepath << "\"" << std::endl;
				return nullptr;
			}

			char* data = new char[size];

			in.read(data, size);

			return data;
		}
	private:
		std::shared_ptr<IFileSystem> mFileSystem;
	};
}

SoundLoader::SoundLoader()
	: mImpl(std::make_unique<SoundLoaderImpl>()) { }

SoundLoader::~SoundLoader()
{
	mImpl.reset(nullptr);
}

Engine::Sound SoundLoader::loadSound(const string& fileName)
{
	Engine::Sound sound;
	ALuint buffer;
	unsigned char channels;
	int sampleRate;
	unsigned char bitsPerSample;
	int size;
	auto data = mImpl->load_wav(fileName, channels, sampleRate, bitsPerSample, size);
	
	ALenum format;
    if(channels == 1 && bitsPerSample == 8)
        format = AL_FORMAT_MONO8;
    else if(channels == 1 && bitsPerSample == 16)
        format = AL_FORMAT_MONO16;
    else if(channels == 2 && bitsPerSample == 8)
        format = AL_FORMAT_STEREO8;
    else if(channels == 2 && bitsPerSample == 16)
        format = AL_FORMAT_STEREO16;
    else
    {
        debuglog
            << "ERROR: unrecognised wave format: "
            << channels << " channels, "
            << bitsPerSample << " bps" << std::endl;
		return sound;
    }

	AlGenBuffers(1, &buffer);
	AlBufferData(buffer, format, data, size, sampleRate);
	/* Create the source to play the sound with. */
    unsigned int source = 0;
    AlGenSources(1, &source);
    AlSourcei(source, AL_BUFFER, (ALint)buffer);

    sound.Source = source;
	sound.Channels = channels;
	sound.SampleRate = sampleRate;
	sound.BitsPerSample = bitsPerSample;

	return sound;
}
