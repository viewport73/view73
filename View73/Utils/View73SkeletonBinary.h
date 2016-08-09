/********************************************************************
	filename: 	View73SkeletonBinary
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73SkeletonBinary_h__
#define __View73SkeletonBinary_h__

#include "View73Flag.h"
#include <Utils/View73LogManager.h>
#include <vector>
#include <algorithm>
#include "View73File.h"
#include "../Graphics/View73SkeletonManager.h"
#include "View73StringTokenizer.h"

namespace View73
{
	class SkeletonBinary
	{
	public:

		static const unsigned gSkeletonBinaryMagicNumber = '\0' << 24 | 'b' << 16 | 's' << 8 | 'p';
		static const char gNameSeperator = '\n'; //used with dataElementType

		enum SBDataElementType
		{
			eSBDET_Float = 0,
			eSBDET_Int,
			eSBDET_UnsignedInt,
			eSBDET_Char,
			eSBDET_Name,
			eSBDET_Float4x4,

			eSBDET_Count,
		};

		enum SBSemantic
		{
			eSBS_None		= 0,
			eSBS_SKELETONNAME,
			eSBS_BONEID,
			eSBS_BONENAME,
			eSBS_TRANSFORM,
			eSBS_CHILDCOUNT,
			eSBS_CHILD,
			eSBS_Count,
		};

		enum ChunkId
		{
			eCI_Header = 0,
			eCI_Skeleton,
		};

		// Total chunk size is 32 bytes 
		class SBFileHeaderChunk
		{
		private:

			unsigned int m_MagicNumber;
			unsigned int m_ChunkId;
			unsigned int m_VersionNumber;
			unsigned int m_FileSize;
			unsigned int m_UnusedData[4]; //for future use //size 4 * 4

		public:

			inline SBFileHeaderChunk()
				: m_MagicNumber(gSkeletonBinaryMagicNumber)
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
		class SBFileSkeletonChunk
		{
		private:

			unsigned int m_ChunkId;
			TFlag32 m_SkeletonSemantic;
			unsigned int m_UnusedData[6];	//For future use //size 4 * 6

		public:

			inline SBFileSkeletonChunk()
				: m_ChunkId(eCI_Skeleton)
			{
			}

			inline ChunkId GetChunkId() const						{	return (ChunkId)m_ChunkId;									}
			inline void AddSemantic( SBSemantic _semantic )			{	m_SkeletonSemantic.SetFlag(1 << _semantic);					}
			inline void RemoveSemantic( SBSemantic _semantic )		{	m_SkeletonSemantic.ClearFlag(1 << _semantic);				}
			inline bool HasSemantic( SBSemantic _semantic )	const	{	return m_SkeletonSemantic.CheckFlag(1 << _semantic);		}
			inline void ClearAllSemantic()							{	m_SkeletonSemantic.ResetFlag();								}
		};

		class SBFileData
		{
		public:

			struct DataBlock
			{
				//each data block header is 32 bytes with m_DataCount = 0
				struct DataBlockHeader
				{
					unsigned int m_SkeletonSemantic;
					unsigned int m_DataElementType;
					unsigned int m_DataElementSize;
					unsigned int m_DataStride;
					unsigned int m_DataCount;
					unsigned int m_UnusedData[3];		// can be utilized in future
					
					inline DataBlockHeader()
						: m_SkeletonSemantic(0)
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

			inline SBFileData()
			{
			}

			inline ~SBFileData()
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
		
		SBFileHeaderChunk			m_FileHeader;
		SBFileSkeletonChunk			m_SkeletonChunck;
		SBFileData					m_Data;
		unsigned int				m_FileSize;
		bool						m_DataLoaded;


	public:

		inline SkeletonBinary(const String& _fileName)
			: m_FileName(_fileName)
			, m_FileSize(0)
			, m_DataLoaded(false)
		{
		}

		inline ~SkeletonBinary()
		{
		}

		inline const String& GetFileName() const						{		return m_FileName;				}
		inline SBFileHeaderChunk& GetFileHeader()						{		return m_FileHeader;			}
		inline const SBFileHeaderChunk& GetFileHeader() const			{		return m_FileHeader;			}
		inline SBFileSkeletonChunk& GetSkeletonChunk()					{		return m_SkeletonChunck;		}
		inline const SBFileSkeletonChunk& GetGeometryChunk() const		{		return m_SkeletonChunck;		}
		inline SBFileData& GetFileData()								{		return m_Data;					}
		inline const SBFileData& GetFileData() const					{		return m_Data;					}

		void ComputeFileSizeFromData() ;
		inline unsigned int GetFileSize() const							{		return m_FileSize;				}
		
		inline void SetDataLoaded()										{		m_DataLoaded = true;			}

		void DumpSkeletonToFile();
		bool LoadFromFile();

		TSharedSkeletonPtr CreateSkeletonWithData();

	private:

		void DumpDataBlockToFile( const SBFileData::DataBlock& _dataBlock, File& _file ) const;
		SBFileData::DataBlock* GetNextDataBlockBySemantic(const SBFileData& _fileData, SBSemantic _semantic, unsigned int& _inOutCurrIndex);
		bool LoadFileDataBlockFromFile( File& _file, SBFileData::DataBlock& _oDataBlock ) const;
		void Reset();

		void SetSkeletonDataToSkeleton(TSharedSkeletonPtr _skeleton);
	};
}

#endif