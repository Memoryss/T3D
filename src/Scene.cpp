#include "Scene.h"

#include <assert.h>

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
		//释放资源
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

		delete iter->second;
		m_models.erase(iter);
	}

	void Scene::RemoveModel(Model * model)
	{
		auto iter = m_models.end();
		for (; iter != m_models.end(); ++iter)
		{
			if (model == iter->second)
			{
				delete iter->second;
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
		m_cameras[name] = cam;
		return cam;
	}

	Camera * Scene::GetCamera(const char * name)
	{
		auto iter = m_cameras.find(name);
		if (iter != m_cameras.end())
		{
			LOG(WARNING) << "can't find camear, name=" << name;
			return NULL;
		}

		return iter->second;
	}

	Light * Scene::AddLight()
	{
		Light *light = new Light(LIGHT_Directional);
		m_lights.push_back(light);

		return light;
	}

	void Scene::RemoveLight(Light *light)
	{
		auto iter = m_lights.begin();
		for (; iter != m_lights.end(); ++iter)
		{
			if (*iter == light)
			{
				delete *iter;
				m_lights.erase(iter);
				return;
			}
		}
	}

	void Scene::ClearLight()
	{
		auto iter = m_lights.begin();
		for (; iter != m_lights.end(); ++iter)
		{
			delete *iter;
		}

		m_lights.clear();
	}

	void Scene::Update()
	{
		if (m_cameras.empty())
		{
			assert(0);
			return;
		}

		//先改变位置，然后渲染
		for each (auto iter in m_models)
		{
			if (iter.second)
			{
				iter.second->Update();
			}
		}

		for each (auto iter in m_cameras)
		{

		}
	}

	void Scene::draw(Camera * cam)
	{
		//渲染模型
		for each(auto iter in m_models)
		{
			if (iter.second)
			{
				iter.second->Draw();
			}
		}
	}

}
