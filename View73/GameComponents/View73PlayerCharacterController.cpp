#include "View73PlayerCharacterController.h"

namespace View73
{
	PlayerCharacterController::PlayerCharacterController(TActorWeakPtr _character)
		: m_Character(_character)
	{
	}

	PlayerCharacterController::~PlayerCharacterController()
	{
		m_Character.reset();
	}
		
	bool PlayerCharacterController::CanRemoveController() const
	{
		return false;
	}
}