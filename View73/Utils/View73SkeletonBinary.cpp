#include "View73SkeletonBinary.h"

namespace View73
{	
	void SkeletonBinary::ComputeFileSizeFromData() 
	{
		const SBFileData::TDataBlockArray& dataBlocksArray = m_Data.GetAllDataBlocks();
		unsigned int dataBlockCount = (unsigned int)dataBlocksArray.size();

		unsigned int size = sizeof(SBFileHeaderChunk) + sizeof(SBFileSkeletonChunk);

		for( unsigned int i = 0 ; i < dataBlockCount ; i++ )
		{
			const SBFileData::DataBlock& dataBlock = *dataBlocksArray[i];
			size += sizeof(SBFileData::DataBlock::DataBlockHeader);
			size += dataBlock.m_DataBlockHeader.m_DataCount * dataBlock.m_DataBlockHeader.m_DataElementSize;
		}

		m_FileSize = size;
	}

	void SkeletonBinary::DumpSkeletonToFile()
	{
		if( !m_DataLoaded )
		{
			View73::gLogManager->WriteLog("Error data not loaded...");
			return;
		}

		const SBFileHeaderChunk &fileHeader = GetFileHeader();
		const SBFileSkeletonChunk &skeleton = GetSkeletonChunk();
		const SBFileData &fileData = GetFileData();

		const String requiredExt = String(".") + (char*)&gSkeletonBinaryMagicNumber;

		const unsigned int fileNameLength = (const unsigned int)m_FileName.Length();
		String extension("");
		String fileNameLocal( m_FileName );

		if( fileNameLength >= 4)
		{
			extension = String( &(m_FileName.CString())[fileNameLength-4] );
		}

		if( extension != requiredExt )
		{
			fileNameLocal = fileNameLocal + requiredExt ;
		}
	
		File file( fileNameLocal );
		bool fileOpen = file.Open(View73::TFlag32( (unsigned int)(File::eFM_Binary | File::eFM_Write)) ); 

		if( fileOpen )
		{
			file.WriteBufferToFile( (const char*)&fileHeader,sizeof(SBFileHeaderChunk));
			file.WriteBufferToFile( (const char*)&skeleton,sizeof(SBFileSkeletonChunk));

			const SBFileData::TDataBlockArray& allDataBlocks = fileData.GetAllDataBlocks();
			const unsigned int dataBlockCount = (unsigned int)allDataBlocks.size();

			for( unsigned int i = 0 ; i < dataBlockCount ; i++ )
			{
				DumpDataBlockToFile(*allDataBlocks[i],file);
			}

			Reset();
		}
		else
		{
			View73::gLogManager->WriteLog(String("Unable to open file '") + fileNameLocal + "'...");
		}

		file.Close();
	}

	void SkeletonBinary::DumpDataBlockToFile( const SBFileData::DataBlock& _dataBlock, File& _file ) const
	{
		_file.WriteBufferToFile( (const char*)&_dataBlock.m_DataBlockHeader,sizeof(SBFileData::DataBlock::DataBlockHeader));

		const float* test = (const float*)_dataBlock.m_Data;
		_file.WriteBufferToFile( (const char*)_dataBlock.m_Data,_dataBlock.GetDataSize());
	}

	void SkeletonBinary::Reset()
	{
		m_FileHeader.SetFileSize(0);
		m_SkeletonChunck.ClearAllSemantic();
		m_Data.Clear();
		m_FileSize = 0;
		m_DataLoaded = false;
	}

	bool SkeletonBinary::LoadFromFile()
	{
		if( m_DataLoaded )
		{
			View73::gLogManager->WriteLog("Error data already loaded...");
			return false;
		}

		SBFileHeaderChunk &fileHeader = GetFileHeader();
		SBFileSkeletonChunk &skeleton = GetSkeletonChunk();
		SBFileData &fileData = GetFileData();

		File file( m_FileName );
		bool open = file.Open(View73::TFlag32( (unsigned int)(File::eFM_Binary | File::eFM_Read)) );

		bool loaded = file.LoadBufferFromFile( (char*)&fileHeader,sizeof(SBFileHeaderChunk));

		if( loaded )
		{
			unsigned int fileSizefromFile = fileHeader.GetFileSize();
			unsigned int fileSize = file.GetFileLength();

			if( fileSizefromFile == fileSize )
			{
				loaded = file.LoadBufferFromFile( (char*)&skeleton,sizeof(SBFileSkeletonChunk));

				if( loaded )
				{
					if( fileHeader.GetMagicNumber() == gSkeletonBinaryMagicNumber && fileHeader.GetChunkId() == eCI_Header )
					{
						if( skeleton.GetChunkId() == eCI_Skeleton )
						{
							if( skeleton.HasSemantic(eSBS_SKELETONNAME) && skeleton.HasSemantic(eSBS_BONEID) 
								&& skeleton.HasSemantic(eSBS_BONENAME) && skeleton.HasSemantic(eSBS_TRANSFORM) 
								&& skeleton.HasSemantic(eSBS_CHILDCOUNT) && skeleton.HasSemantic(eSBS_CHILD) )
							{
								unsigned int sizeofLeftFileData = fileSizefromFile - ( sizeof(SBFileHeaderChunk) + sizeof(SBFileSkeletonChunk) );
								bool failedLoad = false;
								while( sizeofLeftFileData )
								{
									SBFileData::DataBlock* addDataBlock = fileData.AddNewDataBlock();
									if( LoadFileDataBlockFromFile(file,*addDataBlock) )
									{
										sizeofLeftFileData -= sizeof(SBFileData::DataBlock::DataBlockHeader) + addDataBlock->GetDataSize();
									}
									else
									{
										View73::gLogManager->WriteLog("Error occured during loading data block...");
										failedLoad = true;
										break;
									}
								}

								file.Close();

								m_DataLoaded = !failedLoad;

								return !failedLoad;
							}
							else
							{
								View73::gLogManager->WriteLog("Basic data required to build a mesh is not present in the file or file is corrupted...");
							}
						}
						else
						{
							View73::gLogManager->WriteLog("File is corrupted...");
						}
					}
					else
					{
						View73::gLogManager->WriteLog("Wrong file format or file is corrupted...");
					}
				}
			}
			else
			{
				View73::gLogManager->WriteLog("File corrupted...");
			}
		}

		file.Close();

		return false;
	}

	bool SkeletonBinary::LoadFileDataBlockFromFile( File& _file, SBFileData::DataBlock& _oDataBlock ) const
	{
		bool loadedHeader = _file.LoadBufferFromFile((char*)&_oDataBlock.m_DataBlockHeader,sizeof(SBFileData::DataBlock::DataBlockHeader));

		if( loadedHeader && _oDataBlock.GetDataSize() > 0 )
		{
			_oDataBlock.m_Data = static_cast<char*>(malloc(_oDataBlock.GetDataSize()));
			bool loadedData = _file.LoadBufferFromFile(_oDataBlock.m_Data,_oDataBlock.GetDataSize());
			return loadedData;
		}

		return false;
	}

	TSharedSkeletonPtr SkeletonBinary::CreateSkeletonWithData()
	{
		if( !m_DataLoaded )
		{
			bool loaded = LoadFromFile();
			if( !loaded )
			{
				TSharedSkeletonPtr();
			}
		}

		const SBFileHeaderChunk &fileHeader = GetFileHeader();
		const SBFileSkeletonChunk &skeleton = GetSkeletonChunk();
		const SBFileData &fileData = GetFileData();

		unsigned int currIndex = 0;

		SBFileData::DataBlock* meshNameDataBlock = GetNextDataBlockBySemantic(fileData,eSBS_SKELETONNAME,currIndex);

		TSharedSkeletonPtr newSkeleton = gSkeletonManager->CreateSkeleton(meshNameDataBlock->m_Data );

		SetSkeletonDataToSkeleton(newSkeleton);
	
		return newSkeleton;
	}

	SkeletonBinary::SBFileData::DataBlock* SkeletonBinary::GetNextDataBlockBySemantic(const SBFileData& _fileData, SBSemantic _semantic, unsigned int& _inOutCurrIndex)
	{
		const SBFileData::TDataBlockArray& allDataBlocks = _fileData.GetAllDataBlocks();
		const unsigned int count = (unsigned int)allDataBlocks.size();

		for( unsigned int i = _inOutCurrIndex ; i < count ; i++ )
		{
			if( allDataBlocks[i]->m_DataBlockHeader.m_SkeletonSemantic == _semantic )
			{
				_inOutCurrIndex = i;
				return allDataBlocks[i];
			}
		}

		return NULL;
	}

	void SkeletonBinary::SetSkeletonDataToSkeleton(TSharedSkeletonPtr _skeleton)
	{
		if( !m_DataLoaded )
		{
			View73::gLogManager->WriteLog("Error data not loaded...");
			return;
		}

		const SBFileHeaderChunk &fileHeader = GetFileHeader();
		const SBFileSkeletonChunk &skeleton = GetSkeletonChunk();
		const SBFileData &fileData = GetFileData();

		unsigned int currIndex[eSBS_Count];

		for( unsigned int i = 0 ; i < eSBS_Count ; i++ )
		{
			currIndex[i] = 0;
		}

		SBFileData::DataBlock* boneIdDataBlock = GetNextDataBlockBySemantic(fileData,eSBS_BONEID,currIndex[eSBS_BONEID]);
		SBFileData::DataBlock* boneNameDataBlock = GetNextDataBlockBySemantic(fileData,eSBS_BONENAME,currIndex[eSBS_BONENAME]);
		SBFileData::DataBlock* boneTransformBlock = GetNextDataBlockBySemantic(fileData,eSBS_TRANSFORM,currIndex[eSBS_TRANSFORM]);


		if( boneIdDataBlock && boneNameDataBlock )
		{
			String boneNameArray(boneNameDataBlock->m_Data);
			StringTokenizer tokenizer(boneNameArray,gNameSeperator);
			const float* transforms = (const float*)boneTransformBlock->m_Data;

			while( 1 )
			{
				String boneName = tokenizer.GetNextToken();
				Matrix44 currTransform;
				//memcpy(currTransform.arr,transforms,16);

				for( int i = 0 ; i < 16 ; i++ )
				{
					currTransform.arr[i] = transforms[i];
				}

				_skeleton->CreateBoneInfo(boneName,currTransform);

				if( !tokenizer.HasNextToken() )
				{
					break;
				}

				transforms = transforms + 16;
			}
		}

		SBFileData::DataBlock* childsCountDataBlock = GetNextDataBlockBySemantic(fileData,eSBS_CHILDCOUNT,currIndex[eSBS_CHILDCOUNT]);
		SBFileData::DataBlock* childsDataBlock = GetNextDataBlockBySemantic(fileData,eSBS_CHILD,currIndex[eSBS_CHILD]);

		const unsigned int* childsCountData = (const unsigned int*)childsCountDataBlock->m_Data;
		const unsigned int* childsData = (const unsigned int*)childsDataBlock->m_Data;

		unsigned int childIndex = 0;
		for( unsigned int i = 0 ; i < childsCountDataBlock->m_DataBlockHeader.m_DataCount ; i++ )
		{
			const unsigned int currDhildCount = childsCountData[i];

			for( unsigned int j = 0 ; j < currDhildCount ; j++ )
			{
				const unsigned int child = childsData[childIndex++];
				_skeleton->AddChildToBone(i,child);
			}
		}

		Reset();
	}
}