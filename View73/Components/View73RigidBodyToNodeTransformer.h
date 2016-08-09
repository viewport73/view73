/********************************************************************
	filename: 	View73RigidBodyToNodeTransformer
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73RigidBodyToNodeTransformer_h__
#define __View73RigidBodyToNodeTransformer_h__

#include "View73Transformer.h"
#include "../View73BulletPhysics/View73BulletTypes.h"
#include "../Graphics/View73Node.h"

namespace View73
{
	class RigidBodyToNodeTransformer : public Transformer
	{
	private:
		
		TBulletRigidBodySharedPtr m_RigidBody;
		TSharedNodePtr m_Node;

	public:
		
		RigidBodyToNodeTransformer(TBulletRigidBodySharedPtr _rb,TSharedNodePtr _node);
		virtual ~RigidBodyToNodeTransformer();

		virtual void Update(const FrameEvent& _frameEvent);
	};
}

#endif