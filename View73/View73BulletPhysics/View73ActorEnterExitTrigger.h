/********************************************************************
	filename: 	View73ActorEnterExitTrigger
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73ActorEnterExitTrigger_h__
#define __View73ActorEnterExitTrigger_h__


#include "View73Trigger.h"
#include "../GameComponents/View73ActorOrToken.h"
#include "../Components/View73Event.h"

namespace View73
{

	class ActorEnterExitTrigger : public Trigger
	{
	public:

		enum EventType
		{
			ET_OnEnter = 0,
			ET_Inside,
			ET_OnExit,

			ET_Num
		};
	protected:

		TActorTokenSharedPtr m_ActorToCheck;

		bool m_PrvObjectInside;
		TEventSharedPtr m_Events[ET_Num];

	public:

		ActorEnterExitTrigger( const TriggerDesc& _desc ,TActorTokenSharedPtr _actorToCheck);
		virtual ~ActorEnterExitTrigger();

		virtual void Update();

		void AddCommand(TCommandAutoPtr _command, EventType _toEvent);

	private:

		void ProcessObectsInsideGhostObjects(btAlignedObjectArray < btCollisionObject* >& objs, bool isPairCachingGhostObject);
	};
}

#endif