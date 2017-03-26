#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <string>

namespace T3D{

	enum ResourceType
	{
		RT_Mesh = 0,
		RT_Texture,
		RT_Material,

		RT_Count
	};

	class Resource
	{
	public:
		Resource(const char *name, ResourceType type) : m_name(name), m_type(type) {}

		virtual ~Resource() {}

		const char * GetName() const { return m_name.c_str(); }
		ResourceType GetType() const { return m_type; }

	protected:
		std::string m_name;
		ResourceType m_type;
	};

}

#endif