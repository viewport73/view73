/********************************************************************
	filename: 	View73Trigger
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Trigget_h__
#define __View73Trigger_h__

#include "View73BulletTypes.h"
#include "../boost/smart_ptr.hpp"

namespace View73
{
	class Trigger;

	typedef boost::shared_ptr<Trigger> TTriggerSharedPtr;
	typedef boost::weak_ptr<Trigger> TTriggerWeakPtr;
	typedef std::auto_ptr<Trigger> TTriggerAutoPtr;	

	class Trigger
	{
	protected:

		friend class DynamicsWorld;

		TBulletDynamicsWorldSharedPtr m_BulletDynamicsWorld;
		btGhostObject* m_GhostObject;
		btCollisionShape* m_CollisionShape;

		TriggerDesc *m_TriggerDesc;
		
	public:

		Trigger( const TriggerDesc& _desc);
		virtual ~Trigger();

		virtual void Update() = 0;
	private:

		void Initialize(TBulletDynamicsWorldSharedPtr _world);
		void Destroy();
		void ProcessObectsInsideGhostObjects(btAlignedObjectArray < btCollisionObject* >& objs, bool isPairCachingGhostObject);
	};
}

#endif