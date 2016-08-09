/********************************************************************
	filename: 	View73NavMesh
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73NavMesh_h__
#define __View73NavMesh_h__

namespace View73
{
	class NavMesh;

	class NavPolygon
	{
	};

	//=====================================================================
	//Navigation Mesh
	class NavMesh
	{
	private:

		friend class NavPolygon;

		float * const m_Verts;
		unsigned int * const m_Indices;

	public:

		NavMesh(const float* const _verts, unsigned int vertsCount,const unsigned int* _indices,unsigned int indicesCount);
		~NavMesh();
	};
}

#endif