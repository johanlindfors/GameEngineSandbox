#pragma once
#include <memory>
#include <string>

namespace Engine
{
	struct Material;

	class MaterialLoader
	{
	public:
		MaterialLoader() {}

		Material loadMaterial(const std::string &fileName);
	};
}
