/********************************************************************
	filename: 	View73File
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73File_h__
#define __View73File_h__

#include "View73String.h"
#include <iostream>
#include <fstream>
#include "View73Flag.h"

namespace View73
{
	class File
	{
	public:

		enum FileMode
		{
			eFM_None			= 0,
			eFM_Read			= 1 << 0,
			eFM_Write			= 1 << 1, 
			eFM_Binary			= 1 << 2,
		};

		File(const String& _filename);
		~File();

		bool Open(const TFlag32& _modes);
		bool Close();

		inline unsigned long GetFileLength() const	{	return m_FileLength;	}

		bool LoadStringToBuffer( char* _oBuffer, unsigned int _bufferSize );
		bool LoadBufferFromFile( char* _oBuffer, unsigned int _bufferSize );
		bool WriteBufferToFile( const char* _buffer, unsigned int _bufferSize );

	private:

		unsigned long GetFileLength(std::fstream& _file);
		std::ios_base::open_mode GetOpenMode(const TFlag32& _modes);
		bool IsError( bool _read ) const;

		const String m_FileName;
		unsigned long m_FileLength;

		std::fstream m_FileStream;
		bool m_IsFileOpen;
	};
}

#endif