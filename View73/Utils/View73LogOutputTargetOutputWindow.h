/********************************************************************
	filename: 	View73LogOutputTargetOutputWindow
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73LogOutputTargetOutputWindow_h__
#define __View73LogOutputTargetOutputWindow_h__

#include "View73LogOutputTarget.h"

namespace View73
{
	class LogManager;

	class LogOutputTargetOutputWindow : public LogOutputTarget
	{
	public:

		friend class LogManager;

		LogOutputTargetOutputWindow();
		~LogOutputTargetOutputWindow();

	private:

		virtual void WriteLog(const String& _log);
	};
}

#endif