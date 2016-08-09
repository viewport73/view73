/********************************************************************
	filename: 	View73InputManager
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73InputManager_h__
#define __View73InputManager_h__

#include "View73InputSystem.h"

namespace View73
{
	class InputManager
	{
	public:

	private:

		static InputManager *m_Instance;

		TInputSystemSharedPtr m_CurrentInputSystem;

	public:


		//--------------------------------------------------------------------
		//Static functions
		static void CreateInstance();
		static void DestroyInstance();
		static InputManager* Get();
		//--------------------------------------------------------------------

		InputManager();
		~InputManager();

		TInputSystemSharedPtr RegisterInputSystem(TInputSystemAutoPtr _newInputSystem);
		void UnregisterInputSystem();

		void Update(const FrameEvent& _frameEvent);
	};

#define gInputManager InputManager::Get()
}

#endif