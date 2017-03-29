#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <map>

#include "Resource.h"

typedef unsigned int uint32;

namespace T3D{

	typedef std::map<std::string, Resource*> ResourceMap;

	class Texture;
	class Material;

	class ResourceManager
	{
	public:
		
		virtual ~ResourceManager();

		static ResourceManager * Instance();

		virtual Texture* LoadTexture(const char *filename);

		virtual Material* LoadMaterial(const char *filename);

		void SetResourcePath(const char *path);
		const char * GetResourcePath();

		std::string GetAbsolutePath(const char *relative);

	protected:
		ResourceManager(const char *path);

	private:

		static ResourceManager * s_instance;

		ResourceMap m_textures;  //加载的纹理
		ResourceMap m_materials; //加载的材质

		std::string m_path; //资源路径，之后的资源路径都是以此为基准
	};

}

#endif
