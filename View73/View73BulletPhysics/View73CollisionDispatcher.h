/********************************************************************
	filename: 	View73CollisionDispatcher
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73CollisionDispatcher_h__
#define __View73CollisionDispatcher_h__

#include "View73BulletTypes.h"

namespace View73
{
	class CollisionDispatcher : public btCollisionDispatcher
	{
	public:

		CollisionDispatcher(btCollisionConfiguration* collisionConfiguration);
		virtual ~CollisionDispatcher();

		virtual bool needsCollision(btCollisionObject* body0 ,btCollisionObject* body1);
		virtual bool needsResponse(btCollisionObject* body0 ,btCollisionObject* body1);
	};
}

#endif