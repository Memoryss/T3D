#ifndef __SCENE_H__
#define __SCENE_H__

#include <map>
#include <vector>
#include <string>

#include <Vector.h>
#include <Quaternion.h>

namespace T3D {

	class Model;
	class Camera;
	class Light;

	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

		Model * CreateModel(const char *name, const char *path, const Vec3 &pos = Vec3(0, 0, 0), const Quaternion &quat = Quaternion::IDENTITY);
		void AddModel(const char *name, Model *model);
		Model * GetModel(const char *name);

		void RemoveModel(const char *name);
		void RemoveModel(Model *model);

		Camera * CreateCamera(const char *name);
		Camera * GetCamera(const char *name);

		Light * AddLight();
		void RemoveLight(Light *ligth);
		void ClearLight();

		void Update();

	private:
		void draw(Camera *cam);

	private:
		std::map <std::string, Model*> m_models;
		std::map <std::string, Camera*> m_cameras;
		std::vector<Light*> m_lights;
	};

}

#endif