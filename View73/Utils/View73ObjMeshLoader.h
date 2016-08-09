/********************************************************************
	filename: 	View73ObjMeshLoader
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73ObjMeshLoader_h__
#define __View73ObjMeshLoader_h__

#include "../Graphics/View73Mesh.h"
#include "View73CharacterUtils.h"

namespace View73
{
	// model is always suppose to have vertex/texcoord/normals
	class ObjMeshLoader
	{
	public:
		
		enum ObjFileCommands
		{
			OFC_Vertex		= 0,
			OFC_Normal,
			OFC_Face,

			OFC_Count
		};

		ObjMeshLoader();
		~ObjMeshLoader();

		TSharedMeshPtr LoadMesh(const String& _meshFileName);
		bool LoadMesh(const String& _meshFileName,float*& _oVertices,unsigned int& oVertCount,
						unsigned int*& _oIndices,unsigned int& oIndsCount);

	private:

		typedef std::vector<float> TFloatArray;
		typedef std::vector<unsigned int> TUIntArray;

		typedef void (ObjMeshLoader::*CommandFunction)(TCharTokenizerItr,TCharTokenizerItr);

		bool LoadMeshFile(const String& _meshFileName);

		void SetBuffers(TSharedMeshPtr _mesh);
		void AlignBuffersWithTexcoords(TSharedMeshPtr _mesh);
		void AlignBuffersWithVertices(TSharedMeshPtr _mesh);
		void AlignBuffersWithNormals(TSharedMeshPtr _mesh);

		CommandFunction GetCommand(TCharTokenizerItr _command);
		void LoadVertexCommand(TCharTokenizerItr _args, TCharTokenizerItr _end);
		void LoadNormalsCommand(TCharTokenizerItr _args, TCharTokenizerItr _end);
		void LoadFacesCommand(TCharTokenizerItr _args, TCharTokenizerItr _end);
		void AllignArraysWithArray(float* _actualArrayToBe, const TFloatArray& _currArray
			,const TUIntArray& _arrayInds, unsigned int _countPerVal,const TUIntArray& _destArrayInds);

		void ClearAllBuffers();

		template<class T> void CopyBuffers(const std::vector<T>& _src,T*& _dest)
		{
			unsigned int count = (unsigned int)_src.size();

			for(unsigned int i = 0 ; i < count ; i++ )
			{
				_dest[i] = _src[i];
			}
		}
		
		TFloatArray m_Vertices;
		TFloatArray m_Normals;
		TUIntArray m_VertexIndices;
		TUIntArray m_NormalIndices;
		
	};
}

#endif