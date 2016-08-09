/********************************************************************
	filename: 	View73PlayerCharacterController
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73PlayerCharacterController_h__
#define __View73PlayerCharacterController_h__

#include "View73Controller.h"
#include "../Components/View73InputMethodKeyListener.h"
#include "View73Character.h"

namespace View73
{
	class PlayerCharacterController : public Controller , public InputMethodKeyListener
	{
	protected:

		TActorWeakPtr m_Character;

	public:

		PlayerCharacterController(TActorWeakPtr _character);
		virtual ~PlayerCharacterController();

	private:

		virtual bool CanRemoveController() const;
		virtual void Update(const FrameEvent& _frameEvent) = 0;

		virtual bool OnKeyDown(unsigned long _gameKey) = 0;
		virtual bool OnKeyUp(unsigned long _gameKey) = 0;
		virtual bool OnKeyHeld(unsigned long _gameKey) = 0;
		virtual bool OnKeyPressed(unsigned long _gameKey) = 0;
	};
}

#endif