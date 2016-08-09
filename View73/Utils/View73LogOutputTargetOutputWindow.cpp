#include "View73LogOutputTargetOutputWindow.h"

namespace View73
{
	LogOutputTargetOutputWindow::LogOutputTargetOutputWindow()
	{

	}

	LogOutputTargetOutputWindow::~LogOutputTargetOutputWindow()
	{

	}

	void LogOutputTargetOutputWindow::WriteLog(const String& _log)
	{
		printf(_log.CString());
	}
}