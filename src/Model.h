#ifndef _MODEL_H__
#define _MODEL_H__

#include <vector>
#include <map>

#include <Matrix.h>

#include "Node.h"
#include "Mesh.h"
#include "Texture.h"

class aiMesh;
class aiScene;
class aiNode;

namespace T3D {

	class Model : public Node
	{
	public:
		Model();

		void LoadModel(const char *name, const char *modelFilepath);

		virtual void Update() override;

		void Draw();

	private:

		void processNode(aiNode *node, const aiScene *scene);

		//转换material为本地数据结构
		void processMaterial(const aiScene *scene);

		void processMesh(aiMesh *mesh, const aiScene *scene);

		void loadTexture(aiMaterial *material, aiTextureType type);

	private:
		std::vector <Mesh> m_meshs; //模型数据 
		std::map <std::string, Texture*> m_textures; //纹理数据
		std::string m_name;

		Matrix44 m_worldMatrix;
	};

}

#endif 
