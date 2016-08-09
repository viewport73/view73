#include "View73Mesh.h"
#include <boost/assert.hpp>
#include "View73GlInclude.h"
#include "View73Material.h"

namespace
{
	static const unsigned int kGLPolygonModes[View73::Mesh::ePM_Count] = 
											{
												GL_LINES,			//ePM_Lines
												GL_LINE_LOOP,		//ePM_LineLoop
												GL_LINE_STRIP,		//ePM_LineStrip
												GL_TRIANGLES,		//ePM_Triangles
												GL_TRIANGLE_STRIP,	//ePM_TriangleStrip
												GL_TRIANGLE_FAN,	//ePM_TriangleFan
											};
}

namespace View73
{

	//===============================================================================
	//Mesh Implementation

	class Mesh::Impl
	{
	private:

		friend class Mesh;

		TMeshInstancesList		m_InstancesList;

		const String			m_MeshName;

		Mesh*					m_Mesh;

		unsigned int			m_VertexBufferCount;
		float					*m_VertexBuffer;
		
		unsigned int			m_IndexBufferCount;
		unsigned int			*m_IndexBuffer;

		unsigned int			m_TexCoordBufferCount;
		float					*m_TexCoordBuffer;

		unsigned int			m_NormalsBufferCount;
		float					*m_NormalsBuffer;

		//
		String					m_SkeletonName;
		unsigned int			m_BoneCount;
		unsigned int			*m_BoneIndicesBuffer;

		unsigned int			m_VertexWeightBufferCount;
		float					*m_VertexWeightsBuffer;

		Matrix44				m_InverseBindMatrix;
		Matrix44				m_BindShapeMatrix;

		bool					m_Locked;
		Mesh::PolygonMode		m_PolygonMode;

		//===============================================================================
		//MeshInstanceImpl Implementation

		class MeshInstanceImpl : public MeshInstance
		{
		private:

			Mesh* m_Mesh;

			virtual void Render()
			{
				Material::defaultMaterial.ApplyMaterial();
				m_Mesh->Render();
			}

		public:

			MeshInstanceImpl(Mesh* _mesh)
				: MeshInstance()
				, m_Mesh(_mesh)
			{

			}

			~MeshInstanceImpl()
			{
				m_Mesh = NULL;
			}

		};

	public:

		Impl(const String& _meshName,Mesh* _mesh)
			: m_MeshName(_meshName)
			, m_Mesh(_mesh)
			, m_VertexBufferCount(0)
			, m_VertexBuffer(NULL)
			, m_IndexBufferCount(0)
			, m_IndexBuffer(NULL)
			, m_TexCoordBufferCount(0)
			, m_TexCoordBuffer(NULL)
			, m_NormalsBufferCount(0)
			, m_NormalsBuffer(NULL)
			, m_BoneCount(0)
			, m_BoneIndicesBuffer(NULL)
			, m_VertexWeightBufferCount(0)
			, m_VertexWeightsBuffer(NULL)
			, m_InverseBindMatrix(Matrix44::IDENTITY)
			, m_BindShapeMatrix(Matrix44::IDENTITY)
			, m_Locked(false)
			, m_PolygonMode(Mesh::ePM_Triangles)
		{
			
		}

		~Impl()
		{
			Destroy();
		}

		void Destroy()
		{
			ClearVertexBuffer();
			ClearIndexBuffer();
			ClearTexCoordBuffer();
			ClearNormalsBuffer();
			ClearMeshInstances();
			ClearBoneIndicesBuffer();
			ClearVertexWeightsBuffer();
		}

		void ClearVertexBuffer()
		{
			m_VertexBufferCount = 0;
			if(m_VertexBuffer != NULL)
			{
				std::free(m_VertexBuffer);
				m_VertexBuffer = NULL;
			}
		}

		void ClearIndexBuffer()
		{
			m_IndexBufferCount = 0;			
			if(m_IndexBuffer != NULL)
			{
				std::free(m_IndexBuffer);
				m_IndexBuffer = NULL;
			}
		}

		void ClearTexCoordBuffer()
		{
			m_TexCoordBufferCount = 0;

			if(m_TexCoordBuffer != NULL)
			{
				std::free(m_TexCoordBuffer);
				m_TexCoordBuffer = NULL;
			}
		}

		void ClearNormalsBuffer()
		{
			m_NormalsBufferCount = 0;

			if(m_NormalsBuffer != NULL)
			{
				std::free(m_NormalsBuffer);
				m_NormalsBuffer = NULL;
			}
		}

		void ClearBoneIndicesBuffer()
		{
			m_BoneCount = 0;

			if( m_BoneIndicesBuffer != NULL )
			{
				std::free(m_BoneIndicesBuffer);
				m_BoneIndicesBuffer = NULL;
			}
		}

		void ClearVertexWeightsBuffer()
		{
			m_VertexWeightBufferCount = 0;

			if( m_VertexWeightsBuffer != NULL )
			{
				std::free(m_VertexWeightsBuffer);
				m_VertexWeightsBuffer = NULL;
			}
		}

		void ClearMeshInstances()
		{
			TMeshInstancesList::iterator itr = m_InstancesList.begin();
			TMeshInstancesList::iterator end = m_InstancesList.end();

			for( ; itr != end ; itr++ )
			{
				BOOST_ASSERT_MSG((*itr).use_count() == 1, (String("Mesh Instance named ") + m_Mesh->GetName()
					+ " is still in use, first clear the reference before clear.." ).CString() );

				(*itr).reset();
			}

			m_InstancesList.clear();
		}

		inline const String& GetName() const
		{
			return m_MeshName;
		}

		bool SetVertexBuffer(const float* const _vBuffer, unsigned int _vCount)
		{
			BOOST_ASSERT_MSG(m_Locked,"Before modifying mesh first lock it and after finishing unlock it");

			if(m_Locked)
			{
				ClearVertexBuffer();
				m_VertexBufferCount = _vCount;
				m_VertexBuffer = static_cast<float*>(malloc(_vCount * sizeof(float) ) );
				std::memcpy(m_VertexBuffer,_vBuffer,(std::size_t)sizeof(float) * _vCount);
				return true;
			}
			return false;
		}

		bool SetIndexBuffer(const unsigned int* const _iBuffer, unsigned int _iCount)
		{
			BOOST_ASSERT_MSG(m_Locked,"Before modifying mesh first lock it and after finishing unlock it");

			if(m_Locked)
			{
				ClearIndexBuffer();
				m_IndexBufferCount = _iCount;
				m_IndexBuffer = static_cast<unsigned int*>(malloc(_iCount * sizeof(unsigned int) ) );
				std::memcpy(m_IndexBuffer,_iBuffer,(std::size_t)sizeof(unsigned int) * _iCount);
				return true;
			}
			return false;
		}

		bool SetTexCoordBuffer(const float* const _tBuffer, unsigned int _tCount)
		{
			BOOST_ASSERT_MSG(m_Locked,"Before modifying mesh first lock it and after finishing unlock it");

			if(m_Locked)
			{
				ClearTexCoordBuffer();
				m_TexCoordBufferCount = _tCount;
				m_TexCoordBuffer = static_cast<float*>(malloc(_tCount * sizeof(float) ) );
				std::memcpy(m_TexCoordBuffer,_tBuffer,(std::size_t)sizeof(float) * _tCount);
				return true;
			}
			return false;
		}

		bool SetNormalBuffer(const float* const _nBuffer, unsigned int _nCount)
		{
			BOOST_ASSERT_MSG(m_Locked,"Before modifying mesh first lock it and after finishing unlock it");

			if(m_Locked)
			{
				ClearNormalsBuffer();
				m_NormalsBufferCount = _nCount;
				m_NormalsBuffer = static_cast<float*>(malloc(_nCount * sizeof(float) ) );
				std::memcpy(m_NormalsBuffer,_nBuffer,(std::size_t)sizeof(float) * _nCount);
				return true;
			}
			return false;
		}

		bool SetVertexBufferWithDataOwnership(float* _vBuffer, unsigned int _vCount)
		{
			BOOST_ASSERT_MSG(m_Locked,"Before modifying mesh first lock it and after finishing unlock it");

			if(m_Locked)
			{
				ClearVertexBuffer();
				m_VertexBufferCount = _vCount;
				m_VertexBuffer = _vBuffer;
				return true;
			}
			return false;
		}

		bool SetIndexBufferWithDataOwnership(unsigned int* _iBuffer, unsigned int _iCount)
		{
			BOOST_ASSERT_MSG(m_Locked,"Before modifying mesh first lock it and after finishing unlock it");

			if(m_Locked)
			{
				ClearIndexBuffer();
				m_IndexBufferCount = _iCount;
				m_IndexBuffer = _iBuffer;
				return true;
			}
			return false;
		}

		bool SetTexCoordBufferWithDataOwnership(float* _tBuffer, unsigned int _tCount)
		{
			BOOST_ASSERT_MSG(m_Locked,"Before modifying mesh first lock it and after finishing unlock it");

			if(m_Locked)
			{
				ClearTexCoordBuffer();
				m_TexCoordBufferCount = _tCount;
				m_TexCoordBuffer = _tBuffer;
				return true;
			}
			return false;
		}

		bool SetNormalBufferWithDataOwnership(float* _nBuffer, unsigned int _nCount)
		{
			BOOST_ASSERT_MSG(m_Locked,"Before modifying mesh first lock it and after finishing unlock it");

			if(m_Locked)
			{
				ClearNormalsBuffer();
				m_NormalsBufferCount = _nCount;
				m_NormalsBuffer = _nBuffer;
				return true;
			}
			return false;
		}

		bool SetBoneIndicesWithDataOwnership(unsigned int* _boneIndBuffer, unsigned int _boneCount)
		{
			BOOST_ASSERT_MSG(m_Locked,"Before modifying mesh first lock it and after finishing unlock it");

			if(m_Locked)
			{
				ClearNormalsBuffer();
				m_BoneCount = _boneCount;
				m_BoneIndicesBuffer = _boneIndBuffer;
				return true;
			}
			return false;
		}

		bool SetVertexWeightBufferWithDataOwnership(float* _weightBuffer, unsigned int _weightCount)
		{
			BOOST_ASSERT_MSG(m_Locked,"Before modifying mesh first lock it and after finishing unlock it");

			if(m_Locked)
			{
				ClearVertexWeightsBuffer();
				m_VertexWeightBufferCount = _weightCount;
				m_VertexWeightsBuffer = _weightBuffer;
				return true;
			}
			return false;
		}

		void SetInverseBindMatrix(const Matrix44& _matrix)
		{
			m_InverseBindMatrix = _matrix;
		}

		void SetBindShapeMatrix(const Matrix44& _matrix)
		{
			m_BindShapeMatrix = _matrix;
		}

		inline void Lock()
		{
			m_Locked = true;
		}

		inline void Unlock()
		{
			m_Locked = false;
		}

		void Render()
		{
			if(!m_Locked)
			{
				if(m_NormalsBufferCount > 0 && m_NormalsBuffer)
				{
					glEnableClientState(GL_NORMAL_ARRAY);
					glNormalPointer(GL_FLOAT,0,&m_NormalsBuffer[0]);
				}

				glEnableClientState(GL_VERTEX_ARRAY);
				glVertexPointer(3, GL_FLOAT, 0, &m_VertexBuffer[0]);

				glDrawElements(kGLPolygonModes[m_PolygonMode], m_IndexBufferCount,GL_UNSIGNED_INT, &m_IndexBuffer[0]);
			}
		}

		TSharedMeshInstancePtr CreateMeshInstance()
		{
			TSharedMeshInstancePtr meshInstance(new MeshInstanceImpl(m_Mesh));
			m_InstancesList.push_back(meshInstance);
			return meshInstance;
		}
	};

	

	//===============================================================================

	Mesh::Mesh(const String& _meshName)
	{
		m_Impl.reset(new Impl(_meshName,this));
	}
	
	Mesh::~Mesh()
	{
	}

	const String& Mesh::GetName() const
	{
		return m_Impl->GetName();
	}

	bool Mesh::SetVertexBuffer(const float* const _vBuffer, unsigned int _vCount)
	{
		return m_Impl->SetVertexBuffer(_vBuffer,_vCount);
	}

	bool Mesh::SetIndexBuffer(const unsigned int* const _iBuffer, unsigned int _iCount)
	{
		return m_Impl->SetIndexBuffer(_iBuffer,_iCount);
	}

	bool Mesh::SetTexCoordBuffer(const float* const _tBuffer, unsigned int _tCount)
	{
		return m_Impl->SetTexCoordBuffer(_tBuffer,_tCount);
	}

	bool Mesh::SetNormalBuffer(const float* const _nBuffer, unsigned int _nCount)
	{
		return m_Impl->SetNormalBuffer(_nBuffer,_nCount);
	}

	bool Mesh::SetVertexBufferWithDataOwnership(float* _vBuffer, unsigned int _vCount)
	{
		return m_Impl->SetVertexBufferWithDataOwnership( _vBuffer, _vCount);
	}

	bool Mesh::SetIndexBufferWithDataOwnership(unsigned int* _iBuffer, unsigned int _iCount)
	{
		return m_Impl->SetIndexBufferWithDataOwnership( _iBuffer, _iCount);
	}

	bool Mesh::SetTexCoordBufferWithDataOwnership(float* _tBuffer, unsigned int _tCount)
	{
		return m_Impl->SetTexCoordBufferWithDataOwnership( _tBuffer, _tCount);
	}

	bool Mesh::SetNormalBufferWithDataOwnership(float* _nBuffer, unsigned int _nCount)
	{
		return m_Impl->SetNormalBufferWithDataOwnership( _nBuffer, _nCount);
	}

	void Mesh::Lock()
	{
		m_Impl->Lock();
	}

	void Mesh::Unlock()
	{
		m_Impl->Unlock();
	}

	void Mesh::Render()
	{
		m_Impl->Render();
	}

	TSharedMeshInstancePtr Mesh::CreateMeshInstance() const
	{
		return m_Impl->CreateMeshInstance();
	}

	void Mesh::SetSkeletonName( const String& _name )
	{
		m_Impl->m_SkeletonName = _name;
	}

	const String& Mesh::GetSkeletonName() const
	{
		return m_Impl->m_SkeletonName;
	}

	bool Mesh::SetBoneIndicesWithDataOwnership(unsigned int* _boneIndBuffer, unsigned int _boneCount)
	{
		return m_Impl->SetBoneIndicesWithDataOwnership(_boneIndBuffer,_boneCount);
	}

	bool Mesh::SetVertexWeightBufferWithDataOwnership(float* _weightBuffer, unsigned int _weightCount)
	{
		return m_Impl->SetVertexWeightBufferWithDataOwnership(_weightBuffer,_weightCount);
	}

	void Mesh::SetInverseBindMatrix(const Matrix44& _matrix)
	{
		m_Impl->SetInverseBindMatrix(_matrix);
	}

	void Mesh::SetBindShapeMatrix(const Matrix44& _matrix)
	{
		m_Impl->SetBindShapeMatrix(_matrix);
	}
}