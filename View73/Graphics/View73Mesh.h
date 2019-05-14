/********************************************************************
	filename: 	View73Mesh
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Mesh_h__
#define __View73Mesh_h__

#include <boost/smart_ptr.hpp>
#include <vector>
#include <list>
#include "../Math/View73Vector3.h"
#include "../Math/View73Matrix44.h"
#include "View73MeshInstance.h"
#include "../Utils/View73String.h"


namespace View73
{
	class Mesh;

	typedef boost::shared_ptr<Mesh> TSharedMeshPtr;

	typedef std::list<TSharedMeshPtr> TSharedMeshPtrList;

	class Mesh
	{
	public:

		enum PolygonMode
		{
			ePM_Lines = 0,
			ePM_LineLoop,
			ePM_LineStrip,
			ePM_Triangles,
			ePM_TriangleStrip,
			ePM_TriangleFan,

			ePM_Count
		};

	private:

		class Impl;
		boost::scoped_ptr<Impl> m_Impl;

	public:
		Mesh(const String& _meshName);
		virtual ~Mesh();

		const String& GetName() const;

		TSharedMeshInstancePtr CreateMeshInstance() const;

		bool SetVertexBuffer(const float* const _vBuffer, unsigned int _vCount);
		bool SetIndexBuffer(const unsigned int* const _iBuffer, unsigned int _iCount);
		bool SetTexCoordBuffer(const float* const _tBuffer, unsigned int _tCount);
		bool SetNormalBuffer(const float* const _nBuffer, unsigned int _nCount);

		bool SetVertexBufferWithDataOwnership(float* _vBuffer, unsigned int _vCount);
		bool SetIndexBufferWithDataOwnership(unsigned int* _iBuffer, unsigned int _iCount);
		bool SetTexCoordBufferWithDataOwnership(float* _tBuffer, unsigned int _tCount);
		bool SetNormalBufferWithDataOwnership(float* _nBuffer, unsigned int _nCount);

		void SetSkeletonName( const String& _name );
		const String& GetSkeletonName() const;

		bool SetBoneIndicesWithDataOwnership(unsigned int* _boneIndBuffer, unsigned int _boneCount);
		bool SetVertexWeightBufferWithDataOwnership(float* _weightBuffer, unsigned int _weightCount);

		void SetInverseBindMatrix(const Matrix44& _matrix);
		void SetBindShapeMatrix(const Matrix44& _matrix);

		void Lock();
		void Unlock();

		void Render();
	};

	
}

#endif