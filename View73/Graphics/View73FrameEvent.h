/********************************************************************
	filename: 	View73FrameEvent
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73FrameEvent_h__
#define __View73FrameEvent_h__

namespace View73
{
	class FrameEvent
	{
	public:
		FrameEvent(): deltaTimeSecond(0.0f){}
		~FrameEvent(){}

		float deltaTimeSecond;
	};
}

#endif