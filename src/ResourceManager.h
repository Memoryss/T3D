#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <map>
#include <vector>

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

		Texture * LoadTexture(const char *filename);
		Texture * GetTexture(const char *filename);

		Material * AddMaterial();
		Material * GetMaterial(uint32 index);

		void SetResourcePath(const char *path);
		const char * GetResourcePath();

		std::string GetAbsolutePath(const char *relative);

	protected:
		ResourceManager(const char *path);

	private:

		static ResourceManager * s_instance;

		ResourceMap m_textures;  //���ص�����
		std::vector<Material *> m_materials; //���صĲ���

		std::string m_path; //��Դ·����֮�����Դ·�������Դ�Ϊ��׼
	};

}

#endif
