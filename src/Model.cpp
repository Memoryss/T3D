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
			//设置顶点数据
			tmesh.m_vertics[i].SetData(mesh, i);
		}

		tmesh.m_numFaces = mesh->mNumFaces;
		tmesh.m_faces = new Face[mesh->mNumFaces];
		for (uint32 i = 0; i < mesh->mNumFaces; ++i)
		{
			//设置面数据
			const auto &face = mesh->mFaces[i];
			tmesh.m_faces[i].m_numIndices = face.mNumIndices;
			tmesh.m_faces[i].m_indices = new uint32[face.mNumIndices];
			for (uint32 j = 0; j < face.mNumIndices; ++j)
			{
				tmesh.m_faces[i].m_indices[j] = face.mIndices[j];
			}
		}

		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
			loadMatrixTextures(material, aiTextureType_DIFFUSE); //diffuse贴图
			loadMatrixTextures(material, aiTextureType_SPECULAR);
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

	void Model::loadMatrixTextures(aiMaterial *material, aiTextureType type)
	{
		for (uint32 i = 0; i < material->GetTextureCount(type); ++i)
		{
			aiString path;
			material->GetTexture(type, i, &path);
			Texture *texture = new Texture(path.C_Str(), type);
			auto iter = m_textures.find(path.C_Str());
			if (iter != m_textures.end())
			{
				LOG(WARNING) << "Texture has been loaded ,name=" << path.C_Str();
				break;
			}
			
			m_textures[path.C_Str()] = texture;
		}
	}
}