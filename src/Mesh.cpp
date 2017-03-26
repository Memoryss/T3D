#include "Mesh.h"

#include <assimp/mesh.h>

namespace T3D {

	void Vertex::SetData(aiMesh *mesh, uint32 index)
	{
		position.x = mesh->mVertices[index].x;
		position.y = mesh->mVertices[index].y;
		position.z = mesh->mVertices[index].z;

		normal.x = mesh->mNormals[index].x;
		normal.y = mesh->mNormals[index].y;
		normal.z = mesh->mNormals[index].z;

		tangent.x = mesh->mTangents[index].x;
		tangent.y = mesh->mTangents[index].y;
		tangent.z = mesh->mTangents[index].z;

		bitangent.x = mesh->mBitangents[index].x;
		bitangent.y = mesh->mBitangents[index].y;
		bitangent.z = mesh->mBitangents[index].z;

		if (mesh->mTextureCoords[0])
		{
			texcoord.x = mesh->mTextureCoords[0]->x;
			texcoord.y = mesh->mTextureCoords[0]->y;
		}
		else
		{
			texcoord.x = 0;
			texcoord.y = 0;
		}
	}

	Mesh::Mesh() : m_numVertices(0), m_numPrimitives(0), m_vertics(NULL), m_primitives(NULL)
	{

	}

	Mesh::~Mesh()
	{
		delete[]m_vertics;
		delete[]m_primitives;

	}

	/*
	uint32 Mesh::GetNumUVChannels() const
	{
		if (m_numVertices > 0) 
		{
			return m_vertics[0].texcoord.size();
		}

		return 0;
	}
	*/
	/*
	uint32 Mesh::GetNumColorChannels() const
	{
		if (m_numVertices > 0)
		{
			return m_vertics[0].color.size();
		}

		return 0;
	}
	*/

	void Mesh::Draw()
	{
		for (uint32 i = 0; i < m_)
	}

}