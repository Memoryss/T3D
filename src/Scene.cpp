#include "Scene.h"

#include <glog/logging.h>

#include "Model.h"
#include "Camera.h"
#include "Light.h"

namespace T3D {

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
		//ÊÍ·Å×ÊÔ´
		auto mIter = m_models.begin();
		for (; mIter != m_models.end(); ++mIter)
		{
			if (mIter->second)
			{
				delete mIter->second;
			}				
		}

		auto cIter = m_cameras.begin();
		for (; cIter != m_cameras.end(); ++cIter)
		{
			if (cIter->second)
			{
				delete cIter->second;
			}
		}

		ClearLight();
	}

	Model * Scene::CreateModel(const char * name, const char * path, const Vec3 & pos, const Quaternion & quat)
	{
		auto iter = m_models.find(name);
		if (iter != m_models.end())
		{
			return iter->second;
		}

		Model *model = new Model;
		model->LoadModel(path);

		m_models[name] = model;
	}

	void Scene::AddModel(const char * name, Model * model)
	{
		auto iter = m_models.find(name);
		if (iter != m_models.end())
		{
			LOG(WARNING) << "Model has been added, name=" << name;
			return;
		}

		m_models[name] = model;
	}

	Model * Scene::GetModel(const char * name)
	{
		return nullptr;
	}

	void Scene::RemoveModel(const char * name)
	{
	}

	void Scene::RemoveModel(Model * model)
	{
	}

	Camera * Scene::CreateCamera(const char * name)
	{
		return nullptr;
	}

	Camera * Scene::GetCamera(const char * name)
	{
		return nullptr;
	}

	Light * Scene::AddLight()
	{
		return nullptr;
	}

	void Scene::RemoveLight()
	{
	}

	void Scene::ClearLight()
	{
	}

	void Scene::Update()
	{
	}

}
