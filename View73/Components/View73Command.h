/********************************************************************
	filename: 	View73Command
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Command_h__
#define __View73Command_h__

#include <boost/smart_ptr.hpp>

namespace View73
{
	class Command;

	typedef boost::shared_ptr<Command> TCommandSharedPtr;
	typedef boost::weak_ptr<Command> TCommandWeakPtr;
	typedef std::auto_ptr<Command> TCommandAutoPtr;	

	class Command
	{
	public:
		Command(){}
		virtual ~Command(){}

		virtual void Execute() = 0;

	};
}

#endif