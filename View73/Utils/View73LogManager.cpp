#include "View73LogManager.h"
#include "View73LogOutputTargetOutputWindow.h"

namespace View73
{
	LogManager *LogManager::m_Instance = NULL;

	LogManager::LogManager()
	{
		m_OutputTargetsList.push_back(TSharedLogOPTargetPtr(new LogOutputTargetOutputWindow()) );
	}

	LogManager::~LogManager()
	{
		Destroy();
	}

	void LogManager::Destroy()
	{
		int count = (int)m_OutputTargetsList.size();

		for(int i = 0 ; i < count ; i++)
		{
			BOOST_ASSERT_MSG(m_OutputTargetsList[i].use_count() == 1,"Output Target is still in use, please clear other references" );

			m_OutputTargetsList[i].reset();
		}
	}

	void LogManager::WriteLog(const String& _log)
	{
		int count = (int)m_OutputTargetsList.size();

		for(int i = 0 ; i < count ; i++)
		{
			m_OutputTargetsList[i]->WriteLog(_log);
			m_OutputTargetsList[i]->WriteLog("\n");
		}
	}

	void LogManager::WriteErrorLog(const String& _log)
	{
		int count = (int)m_OutputTargetsList.size();

		for(int i = 0 ; i < count ; i++)
		{
			m_OutputTargetsList[i]->WriteLog("Error : ");
			m_OutputTargetsList[i]->WriteLog(_log);
			m_OutputTargetsList[i]->WriteLog("\n");
		}
	}

	void LogManager::WriteWarningLog(const String& _log)
	{
		int count = (int)m_OutputTargetsList.size();

		for(int i = 0 ; i < count ; i++)
		{
			m_OutputTargetsList[i]->WriteLog("Warning : ");
			m_OutputTargetsList[i]->WriteLog(_log);
			m_OutputTargetsList[i]->WriteLog("\n");
		}
	}

	//--------------------------------------------------------------------
	//Static functions
	void LogManager::CreateInstance()
	{
		if(!m_Instance)
		{
			m_Instance = new LogManager();
		}
	}

	void LogManager::DestroyInstance()
	{
		if(m_Instance)
		{
			delete m_Instance;
			m_Instance = NULL;
		}
	}

	LogManager* LogManager::Get()
	{
		return m_Instance;
	}
	//--------------------------------------------------------------------
}