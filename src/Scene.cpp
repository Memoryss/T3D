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
			LOG(INFO) << "Model has been created, name=" << name;
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
		auto iter = m_models.find(name);
		if (iter != m_models.end())
		{
			LOG(WARNING) << "can't find model, name=" << name;
			return NULL;
		}

		return iter->second;
	}

	void Scene::RemoveModel(const char * name)
	{
		auto iter = m_models.find(name);
		if (iter != m_models.end())
		{
			LOG(WARNING) << "can't find model, name=" << name;
		}

		m_models.erase(iter);
	}

	void Scene::RemoveModel(Model * model)
	{
		auto iter = m_models.end();
		for (; iter != m_models.end(); ++iter)
		{
			if (model == iter->second)
			{
				m_models.erase(iter);
				return;
			}
		}
	}

	Camera * Scene::CreateCamera(const char * name)
	{
		auto iter = m_cameras.find(name);
		if (iter != m_cameras.end())
		{
			LOG(INFO) << "Camera has been created, name=" << name;
			return iter->second;
		}

		Camera *cam = new Camera;
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
