#include "ResourceManager.h"

#include "Texture.h"
#include "Material.h"

namespace T3D {

	ResourceManager * ResourceManager::s_instance = NULL;

	ResourceManager::ResourceManager(const char *path) : m_path(path)
	{

	}

	ResourceManager::~ResourceManager()
	{
		auto texIter = m_textures.begin();
		for (texIter; texIter != m_textures.end(); ++texIter)
		{
			delete texIter->second;
		}

		auto matIter = m_materials.begin();
		for (matIter; matIter != m_materials.end(); ++matIter)
		{
			delete matIter->second;
		}
	}

	Texture * ResourceManager::LoadMaterial()

}