#include "ResourceManager.h"

#include <assert.h>

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

	const char * ResourceManager::GetResourcePath()
	{
		return m_path.c_str();
	}

	ResourceManager * ResourceManager::Instance(const char *path)
	{
		if (s_instance == NULL) 
		{
			s_instance = new ResourceManager(path);
		}

		return s_instance;
	}

	const Texture * ResourceManager::LoadTexture(const char *filename)
	{
		auto iter = m_textures.find(filename);
		if (iter != m_textures.end())
		{
			return static_cast<Texture*>(iter->second);
		}

		auto texture = new Texture(filename);
		std::string 
		texture->ReadFile()
	}

	const Material * ResourceManager::LoadMaterial(const char *filename)
	{

	}

}