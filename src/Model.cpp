#include "Model.h"

#include <tchar.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/color4.h>

#include <glog/logging.h>

#include "ResourceManager.h"
#include "TFile.h"

namespace T3D {

	Model::Model() 
	{
		
	}

	void Model::LoadModel(const char *name, const char *modelFilepath)
	{
		m_name = name;

		Assimp::Importer importer;
		//flag 转化为三角形，生成法线，合并mesh
		std::string meshPath = ResourceManager::Instance()->GetAbsolutePath(modelFilepath);
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
			processMaterial(scene->mMaterials[mesh->mMaterialIndex], tmesh);
		}
	}

	void Model::processNode(aiNode *node, const aiScene *scene)
	{
		//处理父节点的mesh
		for (uint32 i = 0; i < node->mNumMeshes; ++i)
		{
			//所有的mesh保存在scene中，子节点只保存其索引
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			processMesh(mesh, scene);
		}

		//处理子节点
		for (uint32 index = 0; index < node->mNumChildren; ++index)
		{
			processNode(node->mChildren[index]; scene);
		}
	}

	void Model::processMaterial(const aiMaterial *material, Mesh &mesh)
	{
		aiColor4D diffuse;
		aiColor4D specular;
		aiColor4D ambient;
		aiColor4D emission;
		float shininess;
		uint32 max;

		auto mtl = ResourceManager::Instance()->AddMaterial();

		if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
		{
			mtl->m_diffuse = diffuse;
		}

		if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specular))
		{
			mtl->m_specular = specular;
		}

		if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambient))
		{
			mtl->m_ambient = ambient;
		}

		if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &emission))
		{
			mtl->m_emission = emission;
		}

		max = 1;
		if (AI_SUCCESS == aiGetMaterialFloatArray(material, AI_MATKEY_SHININESS, &shininess, &max))
		{
			mtl->m_shininess = shininess;
		}

		//加载纹理
		int index = aiTextureType_NONE;
		for (++index; index < aiTextureType_UNKNOWN; ++index)
		{
			loadTexture(material, (aiTextureType)index, mtl);
		}

		mesh.m_materials = mtl;
	}
	void Model::loadTexture(const aiMaterial * material, aiTextureType type, Material *mtl)
	{
		for (uint32 i = 0; i < material->GetTextureCount(type); ++i)
		{
			aiString path;
			if (AI_SUCCESS == material->GetTexture(type, i, &path))
			{
				Texture *texture = ResourceManager::Instance()->LoadTexture(path.C_Str());
				m_textures[path.C_Str()] = texture;
				mtl->m_textures[type].push_back(texture);
			}
		}
	}
	/*
	void Model::loadMaterial(const char * path)
	{
		std::vector<Material *> materials;
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

				if (0 == _tcscmp(strLine.c_str(), _T("#"))) continue;
				if (0 == _tcscmp(strLine.c_str(), _T("\n"))) continue;

				//new mtl
				if (0 == _tcscmp(strLine.c_str(), _T("newmtl")))
				{
					if (material != NULL)
					{
						materials.push_back(material);  //将之前的material添加进数组中
					}

					std::string name;
					inFile >> name;
					material = new Material(name.c_str());
					continue;
				}
				
				//ambient
				if (0 == _tcscmp(strLine.c_str(), _T("Ka")))
				{
					inFile >> material->m_ambient.r >> material->m_ambient.g >> material->m_ambient.b;
					continue;
				}
				
				// diffuse
				if (0 == _tcscmp(strLine.c_str(), _T("Kd")))
				{
					inFile >> material->m_diffuse.r >> material->m_diffuse.g >> material->m_diffuse.b;
					continue;
				}
				
				// specular
				if (0 == _tcscmp(strLine.c_str(), _T("Ks")))
				{
					inFile >> material->m_specular.r >> material->m_specular.g >> material->m_specular.b;
					continue;
				}
				
				// transmittance
				if (0 == _tcscmp(strLine.c_str(), _T("Tf")))
				{
					inFile >> material->m_transmittance.r >> material->m_transmittance.g >> material->m_transmittance.b;
					continue;
				}

				// ior(index of refraction)
				if (0 == _tcscmp(strLine.c_str(), _T("Ni")))
				{
					inFile >> material->m_ior;
					continue;
				}

				//emission
				if (0 == _tcscmp(strLine.c_str(), _T("Ke")))
				{
					inFile >> material->m_emission.r >> material->m_emission.g >> material->m_emission.b;
					continue;
				}

				//shininess
				if (0 == _tcscmp(strLine.c_str(), _T("Ns")))
				{
					inFile >> material->m_shininess;
					continue;
				}

				//illum model
				if (0 == _tcscmp(strLine.c_str(), _T("illum")))
				{
					inFile >> material->m_illum;
					continue;
				}
				
				//dissolve
				if (0 == _tcscmp(strLine.c_str(), _T("d")))
				{
					inFile >> material->m_dissolve;
					continue;
				}
				if (0 == _tcscmp(strLine.c_str(), _T("Tr")))
				{
					inFile >> material->m_dissolve;
					material->m_dissolve = 1.f - material->m_dissolve;
					continue;
				}

				// PBR: roughness
				if (0 == _tcscmp(strLine.c_str(), _T("Pr")))
				{
					inFile >> material->m_roughness;
					continue;
				}

				// PBR: metallic
				if (0 == _tcscmp(strLine.c_str(), _T("Pm")))
				{
					inFile >> material->m_metallic;
					continue;
				}

				// PBR: sheen
				if (0 == _tcscmp(strLine.c_str(), _T("Ps")))
				{
					inFile >> material->m_sheen;
					continue;
				}

				if (0 == _tcscmp(strLine.c_str(), _T("map_Kd")))
				{
					inFile >> material->m_mapKd;
				}
				
				if (0 == _tcscmp(strLine.c_str(), _T("map_Ks")))
				{
					inFile >> material->m_mapKs;
				}
				
				if (0 == _tcscmp(strLine.c_str(), _T("map_Ka")))
				{
					inFile >> material->m_mapKa;
				}
				
				if (0 == _tcscmp(strLine.c_str(), _T()))
			}
		}
		else
		{
			LOG(ERROR) << "Material load failed, path=" << path;
		}
	}*/
}