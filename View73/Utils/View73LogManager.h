/********************************************************************
	filename: 	View73LogManager
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73LogManager_h__
#define __View73LogManager_h__

#include <vector>
#include "View73LogOutputTarget.h"

namespace View73
{
	class ApplicationRoot;

	class LogManager
	{
	private:

		friend class ApplicationRoot;

		typedef std::vector<TSharedLogOPTargetPtr> TLogOutputTargetsList;

		TLogOutputTargetsList m_OutputTargetsList;

	private:

		LogManager();
		~LogManager();

		void Destroy();

		static LogManager *m_Instance;

	public:

		//--------------------------------------------------------------------
		//Static functions
		static void CreateInstance();
		static void DestroyInstance();
		static LogManager* Get();
		//--------------------------------------------------------------------

		void WriteLog(const String& _log);
		void WriteErrorLog(const String& _log);
		void WriteWarningLog(const String& _log);
	};

#define gLogManager LogManager::Get()
}

#endif