/********************************************************************
	filename: 	View73LogOutputTarget
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73LogOutputTarget_h__
#define __View73LogOutputTarget_h__

#include "../boost/smart_ptr.hpp"
#include "View73String.h"

namespace View73
{
	class LogOutputTarget;

	typedef boost::shared_ptr<LogOutputTarget> TSharedLogOPTargetPtr;
	
	class LogManager;

	class LogOutputTarget
	{
	protected:
		friend class LogManager;

		LogOutputTarget(){}
		virtual ~LogOutputTarget(){}

		virtual void WriteLog(const String& _log) = 0;
	};
}

#endif