/********************************************************************
	filename: 	View73DefaultInputSystem
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73DefaultInputSystem_h__
#define __View73DefaultInputSystem_h__

#include "View73InputSystem.h"

namespace View73
{
	class DefaultInputSystem : public InputSystem
	{
	public:
		
		DefaultInputSystem();
		~DefaultInputSystem();

	private:

		virtual void Update(const FrameEvent& _frameEvent);
	};
}

#endif