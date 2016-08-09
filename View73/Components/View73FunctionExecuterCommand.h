/********************************************************************
	filename: 	View73FunctionExecuterCommand
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73FunctionExecuterCommand_h__
#define __View73FunctionExecuterCommand_h__

#include "View73Command.h"
#include <boost/function.hpp>

namespace View73
{
	typedef boost::function<void ()> TBoostFunction;

	class FunctionExecuterCommand : public Command
	{
	private:
		
		TBoostFunction m_Function;

	public:

		FunctionExecuterCommand(TBoostFunction _function)
			: Command()
			, m_Function(_function)
		{
		}

		virtual ~FunctionExecuterCommand()
		{
		}

		virtual void Execute()
		{
			m_Function();
		}
	};
}

#endif