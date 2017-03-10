#include "Model.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <glog/logging.h>

namespace T3D {

	Model::Model(const char *path) : m_filename(path)
	{
		loadModel();
	}

	void Model::loadModel()
	{
		Assimp::Importer importer;
		//flag 转化为三角形，生成法线，合并mesh
		const aiScene *scene = importer.ReadFile(m_filename, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_OptimizeMeshes);
		if (scene == NULL || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == NULL) {
			LOG(ERROR) << "Load Modeo:" << m_filename << " failed, reason:" << importer.GetErrorString();
			return;
		}

		processNode(scene->mRootNode, scene);
	}

	void Model::processMesh(aiMesh *mesh, const aiScene *scene)
	{
		m_meshs.push_back(Mesh());
		auto &tmesh = m_meshs[m_meshs.size() - 1];
		tmesh.m_vertics = new Vertex[mesh->mNumVertices];
		tmesh.m_numVertices = mesh->mNumVertices;
		for (uint32 i = 0; i < mesh->mNumVertices; ++i)
		{
			tmesh.m_vertics[i].position.x = mesh->mVertices[i].x;
			tmesh.m_vertics[i].position.y = mesh->mVertices[i].y;
			tmesh.m_vertics[i].position.z = mesh->mVertices[i].z;
			tmesh.m_vertics[i]
		}
	}

	void Model::processNode(aiNode *node, const aiScene *scene)
	{
		for (uint32 i = 0; i < node->mNumMeshes; ++i)
		{
			//所有的mesh保存在scene中，子节点只保存其索引
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		}
	}
}