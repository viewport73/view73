#include "View73Event.h"

namespace View73
{
	Event::Event()
	{
	}

	Event::~Event()
	{
		Clear();
	}

	TCommandWeakPtr Event::AddCommand(TCommandAutoPtr _command)
	{
		TCommandSharedPtr cmd(_command.release());
		m_AllCommands.push_back(cmd);
		return cmd;
	}

	void Event::Execute()
	{
		TCommandSharedPtrList::iterator itr = m_AllCommands.begin();
		TCommandSharedPtrList::iterator end = m_AllCommands.end();

		for( ; itr != end ; itr++ )
		{
			(*itr)->Execute();
		}
	}

	void Event::Clear()
	{
		TCommandSharedPtrList::iterator itr = m_AllCommands.begin();
		TCommandSharedPtrList::iterator end = m_AllCommands.end();

		for( ; itr != end ; itr++ )
		{
			BOOST_ASSERT_MSG( (*itr).use_count() == 1, "Command is in use, please clear the reference first" );
			(*itr).reset();
		}

		m_AllCommands.clear();
	}
}