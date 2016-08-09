#include "GameCarController.h"


namespace Game
{
	GameCarController::GameCarController(View73::TActorWeakPtr _car)
		: m_Car(_car)
		, m_LastFrameAcclDecl(false)
		, m_CurrSteering(0.0f)
		, m_LastFrameSteering(false)
		, m_LastFrameThrottleKey(GIK_Num)
	{
		View73::TActorSharedPtr actor = m_Car.lock();
		BOOST_ASSERT_MSG( actor != NULL, "Actor is NULL" );
	}

	GameCarController::~GameCarController()
	{
		//m_Car.release()
	}

	bool GameCarController::CanRemoveController() const
	{
		return false;
	}

	void GameCarController::Update(const View73::FrameEvent& _frameEvent)
	{
		if(!m_LastFrameAcclDecl)
		{
			View73::TActorSharedPtr actor = m_Car.lock();
			BOOST_ASSERT_MSG( actor != NULL, "Actor is NULL" );

			View73::Car *chr = dynamic_cast<View73::Car*>(actor.get());

			chr->SetThrottle(0.0f);
			chr->SetBrake(0.05f);//default brake
		}

		if(!m_LastFrameSteering)
		{
			View73::TActorSharedPtr actor = m_Car.lock();
			BOOST_ASSERT_MSG( actor != NULL, "Actor is NULL" );

			View73::Car *chr = dynamic_cast<View73::Car*>(actor.get());

			m_CurrSteering = chr->GetSteering();
		}

		m_LastFrameAcclDecl = false;
		m_LastFrameSteering = false;
	}

	bool GameCarController::OnKeyDown(unsigned long _gameKey)
	{
		return false;
	}

	bool GameCarController::OnKeyUp(unsigned long _gameKey)
	{
		return false;
	}

	bool GameCarController::OnKeyHeld(unsigned long _gameKey)
	{
		View73::TActorSharedPtr actor = m_Car.lock();
		BOOST_ASSERT_MSG( actor != NULL, "Actor is NULL" );

		View73::Car *chr = dynamic_cast<View73::Car*>(actor.get());


		if(chr)
		{
			switch((GameImputKeys)_gameKey)
			{
			case GIK_Left:
				{
					m_CurrSteering += 0.02f;
					m_CurrSteering = chr->SetSteering(m_CurrSteering);
					m_LastFrameSteering = true;
				}
				break;

			case GIK_Right:
				{
					m_CurrSteering -= 0.02f;
					m_CurrSteering = chr->SetSteering(m_CurrSteering);
					m_LastFrameSteering = true;
				}
				break;

			case GIK_Up:
				{
					if(m_LastFrameThrottleKey == GIK_Up && chr->ComputeSpeed() < 0.0f)
					{
						chr->SetBrake(1.0f);
						chr->SetThrottle(0.0f);
					}
					else
					{
						chr->SetBrake(0.0f);
						chr->SetThrottle(1.0f);
					}

					m_LastFrameAcclDecl = true;
					m_LastFrameThrottleKey = GIK_Up;
				}
				break;

			case GIK_Down:
				{
					if(m_LastFrameThrottleKey == GIK_Down && chr->ComputeSpeed() > 0.0f)
					{
						chr->SetBrake(1.0f);
						chr->SetThrottle(0.0f);
					}
					else
					{
						chr->SetBrake(0.0f);
						chr->SetThrottle(-1.0f);
					}

					m_LastFrameAcclDecl = true;
					m_LastFrameThrottleKey = GIK_Down;
				}
				break;
			
			case GIK_Jump:
				{
				}
				break;
			}

			return true;
		}
		else
		{
			BOOST_ASSERT_MSG( chr != NULL, "Actor is NULL" );
		}

		return false;
	}

	bool GameCarController::OnKeyPressed(unsigned long _gameKey)
	{
		return false;
	}
}