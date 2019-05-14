/********************************************************************
	filename: 	GameCarController
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __GameCarController_h__
#define __GameCarController_h__

#include <boost\make_shared.hpp>

#include "../View73/GameComponents/View73Controller.h"
#include "../View73/Components/View73InputMethodKeyListener.h"
#include "../View73/GameComponents/View73Car.h"
#include "GameInputKeys.h"

namespace Game
{
	class GameCarController;
	typedef boost::shared_ptr<GameCarController> TGameCarControllerSharedPtr;

	class GameCarController : public View73::Controller , public View73::InputMethodKeyListener
	{
	protected:

		View73::TActorWeakPtr m_Car;
		bool m_LastFrameAcclDecl;
		float m_CurrSteering;
		bool m_LastFrameSteering;
		GameImputKeys m_LastFrameThrottleKey;

	public:

		GameCarController(View73::TActorWeakPtr _car);
		virtual ~GameCarController();

	private:

		virtual bool CanRemoveController() const;
		virtual void Update(const View73::FrameEvent& _frameEvent);

		virtual bool OnKeyDown(unsigned long _gameKey);
		virtual bool OnKeyUp(unsigned long _gameKey);
		virtual bool OnKeyHeld(unsigned long _gameKey);
		virtual bool OnKeyPressed(unsigned long _gameKey);
	};
}

#endif