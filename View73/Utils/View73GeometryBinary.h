/********************************************************************
	filename: 	View73GeometryBinary
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73GeometryBinary_h__
#define __View73GeometryBinary_h__

#include "View73Flag.h"
#include <Utils/View73LogManager.h>
#include <vector>
#include <algorithm>
#include "View73File.h"
#include "../Graphics/View73Mesh.h"


#define MAX_NAME_SIZE 64 //this value always needs to be power of 2
#define MAX_NAME_STRING_LENGTH (MAX_NAME_SIZE - 1)

namespace View73
{
	class GeometryBinary
	{
	public:

		static const unsigned gGeometryBinaryMagicNumber = '\0' << 24 | 'b' << 16 | 'g' << 8 | 'p';

		enum GBDataElementType
		{
			eGBDET_Float = 0,
			eGBDET_Int,
			eGBDET_UnsignedInt,
			eGBDET_Char,

			eGBDET_Count,
		};

		enum GBSemantic
		{
			eGBS_None		= 0,
			eGBS_MESHNAME,
			eGBS_POSITION,
			eGBS_NORMAL,
			eGBS_INDICES,
			eGBS_SKELETONNAME,
			eGBS_BONEINDICES,
			eGBS_BONEWEIGHTS,
			eGBS_INVBINDMATRIX,
			eGBS_BINDSHAPEMATRIX,

			eGBS_Count,
		};

		enum ChunkId
		{
			eCI_Header = 0,
			eCI_Geometry,
		};

		// Total chunk size is 32 bytes 
		class GBFileHeaderChunk
		{
		private:

			unsigned int m_MagicNumber;
			unsigned int m_ChunkId;
			unsigned int m_VersionNumber;
			unsigned int m_FileSize;
			unsigned int m_UnusedData[4]; //for future use //size 4 * 4

		public:

			inline GBFileHeaderChunk()
				: m_MagicNumber(gGeometryBinaryMagicNumber)
				, m_VersionNumber(1)
				, m_ChunkId(eCI_Header)
				, m_FileSize(0)
			{
			}

			inline unsigned int GetMagicNumber() const			{		return m_MagicNumber;						}
			inline ChunkId GetChunkId() const					{		return (ChunkId)m_ChunkId;					}
			inline unsigned int GetVersionNumber() const		{		return m_VersionNumber;						}
			inline void SetFileSize(unsigned int _fileSize)		{		m_FileSize = _fileSize;						}
			inline unsigned int GetFileSize() const				{		return m_FileSize;							}
		};

		// Total chunk size is 32 bytes 
		class GBFileGeometryChunk
		{
		private:

			unsigned int m_ChunkId;
			TFlag32 m_VertexSemantic;
			unsigned int m_UnusedData[6];	//For future use //size 4 * 6

		public:

			inline GBFileGeometryChunk()
				: m_ChunkId(eCI_Geometry)
			{
			}

			inline ChunkId GetChunkId() const						{	return (ChunkId)m_ChunkId;					}
			inline void AddSemantic( GBSemantic _semantic )			{	m_VertexSemantic.SetFlag(1 << _semantic);				}
			inline void RemoveSemantic( GBSemantic _semantic )		{	m_VertexSemantic.ClearFlag(1 << _semantic);				}
			inline bool HasSemantic( GBSemantic _semantic )	const	{	return m_VertexSemantic.CheckFlag(1 << _semantic);		}
			inline void ClearAllSemantic()							{	m_VertexSemantic.ResetFlag();							}
		};

		class GBFileData
		{
		public:

			struct DataBlock
			{
				//each data block header is 32 bytes with m_DataCount = 0
				struct DataBlockHeader
				{
					unsigned int m_VertexSemantic;
					unsigned int m_DataElementType;
					unsigned int m_DataElementSize;
					unsigned int m_DataStride;
					unsigned int m_DataCount;
					unsigned int m_UnusedData[3];		// can be utilized in future
					
					inline DataBlockHeader()
						: m_VertexSemantic(0)
						, m_DataElementType(0)
						, m_DataElementSize(0)
						, m_DataStride(0)
						, m_DataCount(0)
					{
					}

					inline ~DataBlockHeader()
					{
						Reset();
					}

					inline void Reset()
					{
						m_DataElementType = 0;
						m_DataElementSize = 0;
						m_DataStride = 0;
						m_DataCount = 0;
					}
				};

				inline DataBlock():m_Data(NULL){}
				inline ~DataBlock()
				{
					if(m_Data)
					{
						std::free(m_Data);
						m_Data = NULL;
					}
				}

				DataBlockHeader m_DataBlockHeader;
				char *m_Data;

				inline unsigned int GetDataSize() const			//GetData Size in bytes
				{
					unsigned int size = m_DataBlockHeader.m_DataElementSize * m_DataBlockHeader.m_DataCount;
					return size;
				}

				inline void RemoveOwnershipFromData()		
				{		
					m_Data = NULL;	
					m_DataBlockHeader.Reset();
				}
			};

			typedef std::vector<DataBlock*> TDataBlockArray;

		private:

			TDataBlockArray m_DataBlocks;

		public:

			inline GBFileData()
			{
			}

			inline ~GBFileData()
			{
				Clear();
			}

			void Clear()
			{
				unsigned int count = (unsigned int)m_DataBlocks.size();
				for( unsigned int i = 0 ; i < count ; i++ )
				{
					delete m_DataBlocks[i];
				}
				m_DataBlocks.clear();
			}
			
			inline DataBlock* AddNewDataBlock()		
			{	
				DataBlock* newDataBlock = new DataBlock();
				m_DataBlocks.push_back(newDataBlock);	
				return newDataBlock;
			}

			void RemoveDataBlock(DataBlock* _dataBlock)
			{
				TDataBlockArray::iterator begin = m_DataBlocks.begin();
				TDataBlockArray::iterator end = m_DataBlocks.end();
				TDataBlockArray::iterator found = end;
				
				found = std::find (begin, end, _dataBlock);

				if( found != end )
				{
					delete *found;
					found = m_DataBlocks.erase(found);
				}
			}

			inline unsigned int DataBlocksCount() const						{		return (unsigned int)m_DataBlocks.size();	}
			inline DataBlock* GetDataBlock( unsigned int _index )			
			{
				if( _index >= DataBlocksCount() )
				{
					return NULL;
				}
				return m_DataBlocks[_index];
			}

			inline const TDataBlockArray& GetAllDataBlocks() const			{		return m_DataBlocks;						}
		};

	private:

		const String				m_FileName;
		
		GBFileHeaderChunk			m_FileHeader;
		GBFileGeometryChunk			m_Geometry;
		GBFileData					m_Data;
		unsigned int				m_FileSize;
		bool						m_DataLoaded;

	public:
		
		inline GeometryBinary(const String& _fileName)
			: m_FileName(_fileName)
			, m_FileSize(0)
			, m_DataLoaded(false)
		{
		}

		inline ~GeometryBinary()
		{
		}

		inline const String& GetFileName() const						{		return m_FileName;				}
		inline GBFileHeaderChunk& GetFileHeader()						{		return m_FileHeader;			}
		inline const GBFileHeaderChunk& GetFileHeader() const			{		return m_FileHeader;			}
		inline GBFileGeometryChunk& GetGeometryChunk()					{		return m_Geometry;				}
		inline const GBFileGeometryChunk& GetGeometryChunk() const		{		return m_Geometry;				}
		inline GBFileData& GetFileData()								{		return m_Data;					}
		inline const GBFileData& GetFileData() const					{		return m_Data;					}

		void ComputeFileSizeFromData() ;
		inline unsigned int GetFileSize() const							{		return m_FileSize;				}
		
		inline void SetDataLoaded()										{		m_DataLoaded = true;				}

		void DumpGeometryToFile();
		bool LoadFromFile();

		TSharedMeshPtr CreateMeshWithData();

	private:

		void DumpDataBlockToFile( const GBFileData::DataBlock& _dataBlock, File& _file ) const;
		GBFileData::DataBlock* GetNextDataBlockBySemantic(const GBFileData& _fileData, GBSemantic _semantic, unsigned int& _inOutCurrIndex);
		bool LoadFileDataBlockFromFile( File& _file, GBFileData::DataBlock& _oDataBlock ) const;
		void Reset();

		void SetGeometryDataToMesh(TSharedMeshPtr _mesh);
	};
}

#endif