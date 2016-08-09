/********************************************************************
	filename: 	View73Event
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Event_h__
#define __View73Event_h__

#include "View73Command.h"
#include <list>

namespace View73
{
	class Event;

	typedef boost::shared_ptr<Event> TEventSharedPtr;
	typedef boost::weak_ptr<Event> TEventWeakPtr;
	typedef std::auto_ptr<Event> TEventAutoPtr;	

	class Event
	{
	public:
		
		typedef std::list<TCommandSharedPtr> TCommandSharedPtrList;

	protected:

		TCommandSharedPtrList m_AllCommands;

	public:

		Event();
		virtual ~Event();

		TCommandWeakPtr AddCommand(TCommandAutoPtr _command);
		virtual void Execute();

	private:
		
		void Clear();
	};
}

#endif