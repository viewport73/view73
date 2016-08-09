#include "View73ObjMeshLoader.h"

#include <iostream>
#include <fstream>

namespace
{
	static const View73::String commandNames[View73::ObjMeshLoader::OFC_Count] = 
											{
												View73::String("v"),				//OFC_Vertex
												View73::String("vn"),				//OFC_Normal
												View73::String("f"),				//OFC_Face
											};
}

namespace View73
{
	ObjMeshLoader::ObjMeshLoader()
	{
	}

	ObjMeshLoader::~ObjMeshLoader()
	{
		ClearAllBuffers();
	}

	void ObjMeshLoader::ClearAllBuffers()
	{
		m_Vertices.clear();
		m_Normals.clear();
		m_VertexIndices.clear();
		m_NormalIndices.clear();
	}

	TSharedMeshPtr ObjMeshLoader::LoadMesh(const String& _meshFileName)
	{
		if(!LoadMeshFile(_meshFileName))
		{
			return TSharedMeshPtr();
		}

		TCharSeperator sep(".");
		const std::string filename(_meshFileName.CString());
 
		TCharTokenizer tokens(filename, sep);
			
		TCharTokenizerItr itr = tokens.begin();

		TSharedMeshPtr newMesh( new Mesh(View73::String(*itr) ) );

		newMesh->Lock();
		SetBuffers(newMesh);
		newMesh->Unlock();
	
		return newMesh;
	}

	bool ObjMeshLoader::LoadMesh(const String& _meshFileName,float*& _oVertices,unsigned int& oVertCount,
		unsigned int*& _oIndices,unsigned int& oIndsCount)
	{
		if(!LoadMeshFile(_meshFileName))
		{
			return false;
		}

		oVertCount = (unsigned int)m_Vertices.size();
		_oVertices = new float[m_Vertices.size()];
		CopyBuffers(m_Vertices,_oVertices);

		oIndsCount = (unsigned int)m_VertexIndices.size();
		_oIndices = new unsigned int[m_VertexIndices.size()];
		CopyBuffers(m_VertexIndices,_oIndices);

		return true;
	}

	bool ObjMeshLoader::LoadMeshFile(const String& _meshFileName)
	{
		ClearAllBuffers();

		std::string str;
		std::ifstream input(_meshFileName.CString(),std::ios_base::in);
		if(input.fail())
		{
			return false;
		}

		TCharTokenizerItr itr;

		while(getline(input,str))
		{
			TCharSeperator sep(" ");
			TCharTokenizer tokens(str, sep);

			itr = tokens.begin();

			if(itr != tokens.end())
			{
				CommandFunction command = GetCommand(itr);
				itr++;

				if(command && itr != tokens.end())
				{
					((*this).*command)(itr,tokens.end());
				}
			}	
		}

		return true;
	}

	void ObjMeshLoader::SetBuffers(TSharedMeshPtr _mesh)
	{
		/*if( (m_TextureList.size()/2) > (m_Vertices.size()/3) 
				&& (m_TextureList.size()/2) > (m_Normals.size()/3) )
		{
			AlignBuffersWithTexcoords(mesh);
		}
		else */if(m_Normals.size() > m_Vertices.size())
		{
			AlignBuffersWithNormals(_mesh);
		}
		else
		{
			AlignBuffersWithVertices(_mesh);
		}
	}

	void ObjMeshLoader::AlignBuffersWithTexcoords(TSharedMeshPtr _mesh)
	{
		/*float vertexBuffer[] = new float[((unsigned int)m_TextureList.size() * 3) / 2];
	    AllignArraysWithArray(vertexBuffer,m_Vertices,m_VertexIndices,(short)3,m_TextCoordIndices);
	    
	    float normalBuffer[] = new float[m_TextureList.size() * 3 / 2];
	    AllignArraysWithArray(normalBuffer,m_Normals,m_NormalIndices,(short)3,m_TextCoordIndices);
	    
	    _mesh->SetVertexBuffer(vertexBuffer,(short)vertexBuffer.length);
	    _mesh->SetIndices(m_TextCoordIndices, (short)m_TextCoordIndices.size());
	    _mesh->SetNormals(normalBuffer);
	    _mesh->SetTexCoords(m_TextureList,(short)m_TextureList.size());*/
	}
	
	void ObjMeshLoader::AlignBuffersWithVertices(TSharedMeshPtr _mesh)
	{
		//float textureBuffer[] = new float[ ((unsigned int)m_Vertices.size() * 2) / 3];
	    //AllignArraysWithArray(textureBuffer,m_TextureList,m_TextCoordIndices,(short)2,m_VertexIndices);
	    
	    float *normalBuffer = new float[m_Vertices.size()];
	    AllignArraysWithArray(normalBuffer,m_Normals,m_NormalIndices,(short)3,m_VertexIndices);

		float *vertices = new float[m_Vertices.size()];
		CopyBuffers(m_Vertices,vertices);

		unsigned int *indices = new unsigned int[m_VertexIndices.size()];
		CopyBuffers(m_VertexIndices,indices);
	    
	    _mesh->SetVertexBuffer(vertices,(int)m_Vertices.size());
	    _mesh->SetIndexBuffer(indices, (int)m_VertexIndices.size());
	    _mesh->SetNormalBuffer(normalBuffer,(int)m_Vertices.size());
	    //_mesh->SetTexCoords(textureBuffer,(int)textureBuffer.length);

		delete [] vertices;
		delete [] indices;
		delete [] normalBuffer;
	}
	
	void ObjMeshLoader::AlignBuffersWithNormals(TSharedMeshPtr _mesh)
	{
		//float[] textureBuffer = new float[m_Normals.size() * 2 / 3];
	    //AllignArraysWithArray(textureBuffer,m_TextureList,m_TextCoordIndices,(int)2,m_NormalIndices);
	    
	    float *vertexBuffer = new float[m_Normals.size()];
	    AllignArraysWithArray(vertexBuffer,m_Vertices,m_VertexIndices,(int)3,m_NormalIndices);

		float *normals = new float[m_Normals.size()];
		CopyBuffers(m_Normals,normals);

		unsigned int *indices = new unsigned int[m_NormalIndices.size()];
		CopyBuffers(m_NormalIndices,indices);
	    
	    _mesh->SetVertexBuffer(vertexBuffer,(int)m_Normals.size());
	    _mesh->SetIndexBuffer(indices, (int)m_NormalIndices.size());
	    _mesh->SetNormalBuffer(normals,(int)m_Normals.size());
	    //_mesh->SetTexCoords(textureBuffer,(int)textureBuffer.length);

		delete [] vertexBuffer;
		delete [] normals;
		delete [] indices;
	}

	ObjMeshLoader::CommandFunction ObjMeshLoader::GetCommand(TCharTokenizerItr _commandNameItr)
	{
		static CommandFunction command[View73::ObjMeshLoader::OFC_Count] = 
											{
												&ObjMeshLoader::LoadVertexCommand,				//OFC_Vertex
												&ObjMeshLoader::LoadNormalsCommand,				//OFC_Normal
												&ObjMeshLoader::LoadFacesCommand,				//OFC_Face
											};
		std::string currCmdName = *_commandNameItr;	

		for(int i = 0 ; i < OFC_Count ; i++)
		{
			if(commandNames[i] == View73::String(currCmdName) )
 			{
				return command[i];
			}
		}

		return NULL;
	}

	void ObjMeshLoader::LoadVertexCommand(TCharTokenizerItr _args, TCharTokenizerItr _end)
	{
		std::string str_x = *(_args++);
		std::string str_y = *(_args++);
		std::string str_z = *(_args++);

		float x,y,z;

		sscanf_s(str_x.c_str(),"%f",&x);
		sscanf_s(str_y.c_str(),"%f",&y);
		sscanf_s(str_z.c_str(),"%f",&z);

		m_Vertices.push_back(x);
		m_Vertices.push_back(y);
		m_Vertices.push_back(z);
	}

	void ObjMeshLoader::LoadNormalsCommand(TCharTokenizerItr _args, TCharTokenizerItr _end)
	{
		std::string str_x = *(_args++);
		std::string str_y = *(_args++);
		std::string str_z = *(_args++);

		float x,y,z;

		sscanf_s(str_x.c_str(),"%f",&x);
		sscanf_s(str_y.c_str(),"%f",&y);
		sscanf_s(str_z.c_str(),"%f",&z);

		m_Normals.push_back(x);
		m_Normals.push_back(y);
		m_Normals.push_back(z);
	}

	void ObjMeshLoader::LoadFacesCommand(TCharTokenizerItr _args, TCharTokenizerItr _end)
	{
		std::string v_text_normal = *(_args++);
	
		TCharSeperator sep("/");
		TCharTokenizer tokens(v_text_normal, sep);

		TCharTokenizerItr itr = tokens.begin();
		
		int count = 0;
		for( ; itr != tokens.end() ; itr++)
		{
			count++;
		}

		assert(count == 3);

		unsigned int vertInd,texInd,normalInd;

		sscanf_s(v_text_normal.c_str(),"%d/%d/%d",&vertInd,&texInd,&normalInd);
		m_VertexIndices.push_back(vertInd-1);
		m_NormalIndices.push_back(normalInd-1);
		//--------------
		v_text_normal = *(_args++);
		sscanf_s(v_text_normal.c_str(),"%d/%d/%d",&vertInd,&texInd,&normalInd);
		m_VertexIndices.push_back(vertInd-1);
		m_NormalIndices.push_back(normalInd-1);
		//--------------
		v_text_normal = *(_args++);
		sscanf_s(v_text_normal.c_str(),"%d/%d/%d",&vertInd,&texInd,&normalInd);
		m_VertexIndices.push_back(vertInd-1);
		m_NormalIndices.push_back(normalInd-1);
	}

	void ObjMeshLoader::AllignArraysWithArray(float* _actualArrayToBe, const TFloatArray& _currArray
			,const TUIntArray& _arrayInds, unsigned int _countPerVal,const TUIntArray& _destArrayInds)
	{
		int numFaces = _destArrayInds.size();
		//actualArrayToBe
		
		for(int i = 0 ; i < numFaces ; i++ )
		{
			int currFace = _destArrayInds[i];
			int currArrInd = _arrayInds[i];
			
			for(unsigned int count = 0 ; count < _countPerVal ; count++)
			{
				_actualArrayToBe[currFace * _countPerVal + count] = _currArray[ currArrInd * _countPerVal + count];
			}
		}
	}
}