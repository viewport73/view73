#include "View73NavMesh.h"

namespace View73
{
	//=====================================================================
	//Navigation Mesh
	NavMesh::NavMesh(const float* const _verts, unsigned int vertsCount,const unsigned int* _indices,unsigned int indicesCount)
		: m_Verts(new float[vertsCount])
		, m_Indices(new unsigned int[indicesCount])
	{
	}

	NavMesh::~NavMesh()
	{
		delete [] m_Verts;
		delete [] m_Indices;
	}
}