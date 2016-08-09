/********************************************************************
	filename: 	View73OnActorInsideTrigger
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73OnActorInsideTrigger_h__
#define __View73OnActorInsideTrigger_h__

#include "View73Trigger.h"
#include "../GameComponents/View73ActorOrToken.h"
#include "../Components/View73Event.h"

namespace View73
{
	class OnActorInsideTrigger : public Trigger
	{
	protected:

		TActorTokenWeakPtr m_ActorToCheck;

		TEventSharedPtr m_ObjectInsideEvent;

	public:

		OnActorInsideTrigger( const TriggerDesc& _desc
			,TActorTokenWeakPtr _actorToCheck);
		virtual ~OnActorInsideTrigger();

		virtual void Update();

		void AddCommand(TCommandAutoPtr _command);

	private:

		void ProcessObectsInsideGhostObjects(btAlignedObjectArray < btCollisionObject* >& objs, bool isPairCachingGhostObject);
	};
}

#endif