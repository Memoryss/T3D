#ifndef _MODEL_H__
#define _MODEL_H__

#include <vector>

#include "Mesh.h"

class aiMesh;
class aiScene;
class aiNode;

namespace T3D {

	class Model
	{
	public:
		Model(const char *path);

		void Draw();

	private:
		void loadModel();

		void processNode(aiNode *node, const aiScene *scene);

		void processMesh(aiMesh *mesh, const aiScene *scene);

	private:
		std::vector <Mesh> m_meshs; //模型数据
		std::string m_filename;
	};

}

#endif 
