#pragma once
#include <memory>
#include <string>

namespace Engine
{
	class Material;

	class MaterialLoader
	{
	public:
		MaterialLoader() {}

		std::shared_ptr<Material> loadMaterial(const std::string &fileName);
	};
}
