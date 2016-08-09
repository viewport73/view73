#include "GamePlayerCharacterController.h"
#include "GameInputKeys.h"

namespace Game
{
	GamePlayerCharacterController::GamePlayerCharacterController(View73::TActorWeakPtr _character)
		: View73::PlayerCharacterController(_character)
	{
		View73::TActorSharedPtr actor = _character.lock();
		BOOST_ASSERT_MSG( actor != NULL, "Actor is NULL" );
	}

	GamePlayerCharacterController::~GamePlayerCharacterController()
	{
	}

	void GamePlayerCharacterController::Update(const View73::FrameEvent& _frameEvent)
	{
		
	}

	bool GamePlayerCharacterController::OnKeyDown(unsigned long _gameKey)
	{
		return false;
	}

	bool GamePlayerCharacterController::OnKeyUp(unsigned long _gameKey)
	{
		return false;
	}

	bool GamePlayerCharacterController::OnKeyHeld(unsigned long _gameKey)
	{
		View73::TActorSharedPtr actor = m_Character.lock();
		BOOST_ASSERT_MSG( actor != NULL, "Actor is NULL" );

		View73::Character *chr = dynamic_cast<View73::Character*>(actor.get());
		if(chr)
		{
			switch((GameImputKeys)_gameKey)
			{
			case GIK_Left:
				{
					chr->SetSpeed(-0.01f);
				}
				break;

			case GIK_Right:
				{
					chr->SetSpeed( 0.01f);
				}
				break;

			case GIK_Up:
				{
				}
				break;

			case GIK_Down:
				{
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

	bool GamePlayerCharacterController::OnKeyPressed(unsigned long _gameKey)
	{
		return false;
	}
}