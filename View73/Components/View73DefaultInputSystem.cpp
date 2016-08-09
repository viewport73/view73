#include "View73DefaultInputSystem.h"

namespace View73
{
	DefaultInputSystem::DefaultInputSystem()
	: InputSystem()
	{
	}

	DefaultInputSystem::~DefaultInputSystem()
	{
	}

	void DefaultInputSystem::Update(const FrameEvent& _frameEvent)
	{
		UpdateAllInputMethods(_frameEvent);
	}
}