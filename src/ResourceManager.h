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

		ResourceMap m_textures;  //���ص�����
		ResourceMap m_materials; //���صĲ���

		std::string m_path; //��Դ·����֮�����Դ·�������Դ�Ϊ��׼
	};

}

#endif
