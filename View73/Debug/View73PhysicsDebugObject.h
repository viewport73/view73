/********************************************************************
	filename: 	View73PhysicsDebugObject
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73PhysicsDebugObject_h__
#define __View73PhysicsDebugObject_h__

#include "View73DebugObject.h"
#include "../View73BulletPhysics/View73DynamicsWorld.h"

namespace View73
{
	class PhysicsDebugObject : public DebugObject
	{
	private:

		TDynamicsWorldWeakPtr m_DynamicsWorld;
	
	public:
	
		PhysicsDebugObject(TDynamicsWorldWeakPtr _dynamicsWorld);
		~PhysicsDebugObject();

		virtual void Render();

	private:

		virtual void DebugDrawerUpdated();
		bool CanDelete() const;
		
	};
}

#endif //__View73PhysicsDebugObject_h__
