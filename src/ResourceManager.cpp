#include "ResourceManager.h"

#include <assert.h>

#include <glog/logging.h>

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

	void ResourceManager::SetResourcePath(const char * path)
	{
		m_path = path;
	}

	const char * ResourceManager::GetResourcePath()
	{
		return m_path.c_str();
	}

	std::string ResourceManager::GetAbsolutePath(const char * relative)
	{
		std::string path(m_path);
		path.append("/");
		path.append(relative);

		return path;
	}

	ResourceManager * ResourceManager::Instance()
	{
		if (s_instance == NULL) 
		{
			s_instance = new ResourceManager(".");
		}

		return s_instance;
	}

	Texture * ResourceManager::LoadTexture(const char *filename)
	{
		auto iter = m_textures.find(filename);
		if (iter != m_textures.end())
		{
			LOG(WARNING) << "Texture has been loaded ,name=" << filename;
			return static_cast<Texture*>(iter->second);
		}

		auto texture = new Texture(filename);
		std::string texPath(m_path);
		m_path.append("/");
		texture->ReadFile(texPath.append(filename).c_str());

		m_textures[filename] = texture;
		return texture;
	}

	Material * ResourceManager::LoadMaterial(const char *filename)
	{
		auto iter = m_materials.find(filename);
		if (iter != m_materials.end())
		{
			return static_cast<Material*>(iter->second);
		}
	}

}