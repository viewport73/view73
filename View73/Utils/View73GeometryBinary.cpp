#include "View73GeometryBinary.h"

namespace View73
{
	void GeometryBinary::ComputeFileSizeFromData() 
	{
		const GBFileData::TDataBlockArray& dataBlocksArray = m_Data.GetAllDataBlocks();
		unsigned int dataBlockCount = (unsigned int)dataBlocksArray.size();

		unsigned int size = sizeof(GBFileHeaderChunk) + sizeof(GBFileGeometryChunk);

		for( unsigned int i = 0 ; i < dataBlockCount ; i++ )
		{
			const GBFileData::DataBlock& dataBlock = *dataBlocksArray[i];
			size += sizeof(GBFileData::DataBlock::DataBlockHeader);
			size += dataBlock.m_DataBlockHeader.m_DataCount * dataBlock.m_DataBlockHeader.m_DataElementSize;
		}

		m_FileSize = size;
	}

	void GeometryBinary::DumpGeometryToFile()
	{
		if( !m_DataLoaded )
		{
			View73::gLogManager->WriteLog("Error data not loaded...");
			return;
		}

		const GBFileHeaderChunk &fileHeader = GetFileHeader();
		const GBFileGeometryChunk &geometry = GetGeometryChunk();
		const GBFileData &fileData = GetFileData();

		/*unsigned int currIndex[eGBS_Count];
		
		for( unsigned int i = 0 ; i < eGBS_Count ; i++ )
		{
			currIndex[i] = 0;
		}

		const GBFileData::DataBlock* meshNameDataBlock = GetNextDataBlockBySemantic(fileData,eGBS_MESHNAME,currIndex[eGBS_MESHNAME]);
		*/

		const String requiredExt = String(".") + (char*)&gGeometryBinaryMagicNumber;

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
			file.WriteBufferToFile( (const char*)&fileHeader,sizeof(GBFileHeaderChunk));
			file.WriteBufferToFile( (const char*)&geometry,sizeof(GBFileGeometryChunk));

			const GBFileData::TDataBlockArray& allDataBlocks = fileData.GetAllDataBlocks();
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

	void GeometryBinary::DumpDataBlockToFile( const GBFileData::DataBlock& _dataBlock, File& _file ) const
	{
		_file.WriteBufferToFile( (const char*)&_dataBlock.m_DataBlockHeader,sizeof(GBFileData::DataBlock::DataBlockHeader));

		const float* test = (const float*)_dataBlock.m_Data;
		_file.WriteBufferToFile( (const char*)_dataBlock.m_Data,_dataBlock.GetDataSize());
	}

	GeometryBinary::GBFileData::DataBlock* GeometryBinary::GetNextDataBlockBySemantic(const GBFileData& _fileData, GBSemantic _semantic, unsigned int& _inOutCurrIndex)
	{
		const GBFileData::TDataBlockArray& allDataBlocks = _fileData.GetAllDataBlocks();
		const unsigned int count = (unsigned int)allDataBlocks.size();

		for( unsigned int i = _inOutCurrIndex ; i < count ; i++ )
		{
			if( allDataBlocks[i]->m_DataBlockHeader.m_VertexSemantic == _semantic )
			{
				_inOutCurrIndex = i;
				return allDataBlocks[i];
			}
		}

		return NULL;
	}

	bool GeometryBinary::LoadFromFile()
	{
		if( m_DataLoaded )
		{
			View73::gLogManager->WriteLog("Error data already loaded...");
			return false;
		}

		GBFileHeaderChunk &fileHeader = GetFileHeader();
		GBFileGeometryChunk &geometry = GetGeometryChunk();
		GBFileData &fileData = GetFileData();

		File file( m_FileName );
		bool open = file.Open(View73::TFlag32( (unsigned int)(File::eFM_Binary | File::eFM_Read)) );

		bool loaded = file.LoadBufferFromFile( (char*)&fileHeader,sizeof(GBFileHeaderChunk));

		if( loaded )
		{
			unsigned int fileSizefromFile = fileHeader.GetFileSize();
			unsigned int fileSize = file.GetFileLength();

			if( fileSizefromFile == fileSize )
			{
				loaded = file.LoadBufferFromFile( (char*)&geometry,sizeof(GBFileGeometryChunk));

				if( loaded )
				{
					if( fileHeader.GetMagicNumber() == gGeometryBinaryMagicNumber && fileHeader.GetChunkId() == eCI_Header )
					{
						if( geometry.GetChunkId() == eCI_Geometry )
						{
							if( geometry.HasSemantic(eGBS_MESHNAME) && geometry.HasSemantic(eGBS_POSITION) && geometry.HasSemantic(eGBS_INDICES) )
							{
								unsigned int sizeofLeftFileData = fileSizefromFile - ( sizeof(GBFileHeaderChunk) + sizeof(GBFileGeometryChunk) );
								bool failedLoad = false;
								while( sizeofLeftFileData )
								{
									GBFileData::DataBlock* addDataBlock = fileData.AddNewDataBlock();
									if( LoadFileDataBlockFromFile(file,*addDataBlock) )
									{
										sizeofLeftFileData -= sizeof(GBFileData::DataBlock::DataBlockHeader) + addDataBlock->GetDataSize();
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

	bool GeometryBinary::LoadFileDataBlockFromFile( File& _file, GBFileData::DataBlock& _oDataBlock ) const
	{
		bool loadedHeader = _file.LoadBufferFromFile((char*)&_oDataBlock.m_DataBlockHeader,sizeof(GBFileData::DataBlock::DataBlockHeader));

		if( loadedHeader && _oDataBlock.GetDataSize() > 0 )
		{
			_oDataBlock.m_Data = static_cast<char*>(malloc(_oDataBlock.GetDataSize()));
			bool loadedData = _file.LoadBufferFromFile(_oDataBlock.m_Data,_oDataBlock.GetDataSize());
			return loadedData;
		}

		return false;
	}

	void GeometryBinary::Reset()
	{
		m_FileHeader.SetFileSize(0);
		m_Geometry.ClearAllSemantic();
		m_Data.Clear();
		m_FileSize = 0;
		m_DataLoaded = false;
	}

	TSharedMeshPtr GeometryBinary::CreateMeshWithData()
	{
		if( !m_DataLoaded )
		{
			bool loaded = LoadFromFile();
			if( !loaded )
			{
				TSharedMeshPtr();
			}
		}

		const GBFileHeaderChunk &fileHeader = GetFileHeader();
		const GBFileGeometryChunk &geometry = GetGeometryChunk();
		const GBFileData &fileData = GetFileData();

		unsigned int currIndex = 0;

		GBFileData::DataBlock* meshNameDataBlock = GetNextDataBlockBySemantic(fileData,eGBS_MESHNAME,currIndex);

		TSharedMeshPtr newMesh(new Mesh(meshNameDataBlock->m_Data ));

		newMesh->Lock();
		SetGeometryDataToMesh(newMesh);
		newMesh->Unlock();

		return newMesh;
	}

	void GeometryBinary::SetGeometryDataToMesh(TSharedMeshPtr _mesh)
	{
		if( !m_DataLoaded )
		{
			View73::gLogManager->WriteLog("Error data not loaded...");
			return;
		}

		const GBFileHeaderChunk &fileHeader = GetFileHeader();
		const GBFileGeometryChunk &geometry = GetGeometryChunk();
		const GBFileData &fileData = GetFileData();

		unsigned int currIndex[eGBS_Count];
		
		for( unsigned int i = 0 ; i < eGBS_Count ; i++ )
		{
			currIndex[i] = 0;
		}

		GBFileData::DataBlock* vertexDataBlock = GetNextDataBlockBySemantic(fileData,eGBS_POSITION,currIndex[eGBS_POSITION]);
		
		if( _mesh->SetVertexBufferWithDataOwnership((float*)vertexDataBlock->m_Data,vertexDataBlock->m_DataBlockHeader.m_DataCount))
		{
			vertexDataBlock->RemoveOwnershipFromData();
		}

		GBFileData::DataBlock* indDataBlock = GetNextDataBlockBySemantic(fileData,eGBS_INDICES,currIndex[eGBS_INDICES]);

		if( _mesh->SetIndexBufferWithDataOwnership((unsigned int*)indDataBlock->m_Data,indDataBlock->m_DataBlockHeader.m_DataCount))
		{
			indDataBlock->RemoveOwnershipFromData();
		}

		GBFileData::DataBlock* normDataBlock = GetNextDataBlockBySemantic(fileData,eGBS_NORMAL,currIndex[eGBS_NORMAL]);

		if( normDataBlock && _mesh->SetNormalBufferWithDataOwnership((float*)normDataBlock->m_Data,normDataBlock->m_DataBlockHeader.m_DataCount))
		{
			normDataBlock->RemoveOwnershipFromData();
		}

		GBFileData::DataBlock* skeletonNameDataBlock = GetNextDataBlockBySemantic(fileData,eGBS_SKELETONNAME,currIndex[eGBS_SKELETONNAME]);

		if(skeletonNameDataBlock)
		{
			_mesh->SetSkeletonName(skeletonNameDataBlock->m_Data);
		}

		GBFileData::DataBlock* boneIndexDataBlock = GetNextDataBlockBySemantic(fileData,eGBS_BONEINDICES,currIndex[eGBS_BONEINDICES]);

		if(boneIndexDataBlock && _mesh->SetBoneIndicesWithDataOwnership((unsigned int*)boneIndexDataBlock->m_Data,boneIndexDataBlock->m_DataBlockHeader.m_DataCount))
		{
			boneIndexDataBlock->RemoveOwnershipFromData();
		}

		GBFileData::DataBlock* boneWeightsDataBlock = GetNextDataBlockBySemantic(fileData,eGBS_BONEWEIGHTS,currIndex[eGBS_BONEWEIGHTS]);

		if(boneWeightsDataBlock && _mesh->SetVertexWeightBufferWithDataOwnership((float*)boneWeightsDataBlock->m_Data,boneWeightsDataBlock->m_DataBlockHeader.m_DataCount))
		{
			boneWeightsDataBlock->RemoveOwnershipFromData();
		}

		GBFileData::DataBlock* invBindMatrix = GetNextDataBlockBySemantic(fileData,eGBS_INVBINDMATRIX,currIndex[eGBS_INVBINDMATRIX]);

		if(invBindMatrix )
		{
			float* floatData = (float*)invBindMatrix->m_Data;
			Matrix44 mat;
			for( int i = 0 ; i < 16 ; i++ )
			{
				mat.arr[i] = floatData[i];
			}

			_mesh->SetInverseBindMatrix(mat);
		}

		GBFileData::DataBlock* bindShapeMatrix = GetNextDataBlockBySemantic(fileData,eGBS_BINDSHAPEMATRIX,currIndex[eGBS_BINDSHAPEMATRIX]);

		if(bindShapeMatrix )
		{
			float* floatData = (float*)bindShapeMatrix->m_Data;
			Matrix44 mat;
			for( int i = 0 ; i < 16 ; i++ )
			{
				mat.arr[i] = floatData[i];
			}

			_mesh->SetBindShapeMatrix(mat);
		}

		Reset();
	}
}