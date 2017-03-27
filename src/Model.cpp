#include "Model.h"

#include <tchar.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glog/logging.h>

#include "ResourceManager.h"
#include "TFile.h"

namespace T3D {

	Model::Model() 
	{
		
	}

	void Model::LoadModel(const char *name, const char *meshFilepath, const char *materialFilepath)
	{
		m_name = name;

		Assimp::Importer importer;
		//flag 转化为三角形，生成法线，合并mesh
		std::string meshPath = ResourceManager::Instance()->GetAbsolutePath(meshFilepath);
		std::string materialPath = ResourceManager::Instance()->GetAbsolutePath(materialFilepath);
		const aiScene *scene = importer.ReadFile(meshPath, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_OptimizeMeshes);
		if (scene == NULL || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == NULL) {
			LOG(ERROR) << "Load Modeo:" << m_name << " failed, reason:" << importer.GetErrorString();
			return;
		}

		processNode(scene->mRootNode, scene);
	}

	void Model::Update()
	{
		//TODO 可以优化成一个函数直接构造，而不是相乘
		//旋转 缩放 平移

		if (!m_dirty)
		{
			return;
		}

		m_worldMatrix = Matrix44::IDENTITY;  // 需要设置为单位矩阵？

		Matrix33 rotateM3;
		m_quat.ToRotationMatrix(rotateM3);
		Matrix44 rotateM4(rotateM3);

		Matrix44 transM = Matrix44::getTrans(m_pos);
		Matrix44 scaleM = Matrix44::getScale(m_scale);

		m_worldMatrix = m_worldMatrix * transM;
		m_worldMatrix = m_worldMatrix * scaleM;
		m_worldMatrix = m_worldMatrix * rotateM4;

		m_dirty = false;
	}

	void Model::Draw()
	{
		if (!m_isVisible)
		{
			return;
		}

		for each(auto iter in m_meshs)
		{
			iter.Draw();
		}
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

		tmesh.m_numPrimitives = mesh->mNumFaces;
		tmesh.m_primitives = new Primitive[mesh->mNumFaces];
		for (uint32 i = 0; i < mesh->mNumFaces; ++i)
		{
			//设置面数据
			const auto &face = mesh->mFaces[i];
			tmesh.m_primitives[i].m_numIndices = face.mNumIndices;
			tmesh.m_primitives[i].m_indices = new uint32[face.mNumIndices];
			for (uint32 j = 0; j < face.mNumIndices; ++j)
			{
				tmesh.m_primitives[i].m_indices[j] = face.mIndices[j];
			}
		}

		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
			loadMatrixTextures(material, aiTextureType_DIFFUSE, tmesh); //diffuse贴图 TODO其他贴图
			loadMatrixTextures(material, aiTextureType_SPECULAR, tmesh);
			loadMatrixTextures(material, aiTextureType_AMBIENT, tmesh);
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

	void Model::loadMatrixTextures(aiMaterial *material, aiTextureType type, Mesh &mesh)
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

	void Model::loadMaterial(const char * path)
	{
		Material *material = NULL;

		TFile materialFile;
		materialFile.Open(path);
		if (materialFile.IsOpen())
		{
			std::string strLine;
			std::stringstream inFile((const char *)materialFile.GetData());
			while (true)
			{
				inFile >> strLine;
				if (!inFile) break;

				if (0 == _tcscmp(strLine.c_str(), _T("#")));
				else if (0 == _tcscmp(strLine.c_str(), _T("newmtl")))
				{
					std::string name;
					inFile >> name;
					material = new Material(name.c_str());
				}
				else if (0 == _tcscmp(strLine, _T("shading")))
			}
		}
		else
		{
			LOG(ERROR) << "Material load failed, path=" << path;
		}
	}
}