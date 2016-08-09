/********************************************************************
	filename: 	BasicCameraController
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __BasicCameraController_h__
#define __BasicCameraController_h__

#include "../View73/Graphics/View73Camera.h"
#include "../View73/GameComponents/View73Actor.h"


namespace Game
{
	class BasicCameraController
	{
	public:
		BasicCameraController(View73::TSharedFrustrumPtr _camera);
		~BasicCameraController();

		void SetFollowActor(View73::TActorWeakPtr _actor);
		void Update(const View73::FrameEvent& _frameEvent);

	private:

		View73::TSharedFrustrumPtr m_SharedCameraPtr;
		View73::TActorWeakPtr m_ActorToFollow;

		float m_LookAtDist;
		View73::Vector3 m_CurrLookAt;
		View73::Vector3 m_CurrPosition;
		const View73::Vector3 m_PositionOffset;
	};
}

#endif