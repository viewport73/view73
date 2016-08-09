/********************************************************************
	filename: 	GamePlayerCharacterController
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __GamePlayerCharacterController_h__
#define __GamePlayerCharacterController_h__

#include "boost/smart_ptr.hpp"
#include "GameComponents/View73PlayerCharacterController.h"

namespace Game
{
	class GamePlayerCharacterController;
	typedef boost::shared_ptr<GamePlayerCharacterController> TGamePlayerCharacterControllerSharedPtr;

	class GamePlayerCharacterController : public View73::PlayerCharacterController
	{
	public:

		GamePlayerCharacterController(View73::TActorWeakPtr _character);
		virtual ~GamePlayerCharacterController();

	private:

		virtual void Update(const View73::FrameEvent& _frameEvent);

		virtual bool OnKeyDown(unsigned long _gameKey);
		virtual bool OnKeyUp(unsigned long _gameKey);
		virtual bool OnKeyHeld(unsigned long _gameKey);
		virtual bool OnKeyPressed(unsigned long _gameKey);
	};
}

#endif