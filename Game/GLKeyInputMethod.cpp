#include "GLKeyInputMethod.h"
#include "GameInputKeys.h"

namespace Game
{
		
	GLKeyInputMethod::GLKeyInputMethod(View73::TInputBindingAutoPtr _inputBinding,Keys* _keys)
	: View73::InputMethodKey(_inputBinding)
	, m_Keys(_keys)
	{
		ResetPreviousPressed();
	}

	GLKeyInputMethod::~GLKeyInputMethod()
	{
	}

	void GLKeyInputMethod::Update(const View73::FrameEvent& _frameEvent)
	{
		for(int i = 0 ; i < GIK_Num ; i++ )
		{
			UpdateGameKey(i);
		}

		UpdateListeners(_frameEvent);
	}

	void GLKeyInputMethod::UpdateGameKey(int _gameKey)
	{
		int key = GetPhysicalKeyFromGameInput(_gameKey);
		bool keyDown = m_Keys->keyDown[key];
		
		bool prevDown = m_PhysicalPrevPressed[_gameKey];

		if(keyDown)
		{
			if(!prevDown)
			{
				m_PhysicalPrevPressed[_gameKey] = true;
				KeyEventHappened(View73::InputMethodKey::GKS_KeyDown,_gameKey,GetTimeForGameInput(_gameKey));
			}
			else
			{
				KeyEventHappened(View73::InputMethodKey::GKS_KeyHeld,_gameKey,GetTimeForGameInput(_gameKey));
			}
		}
		else
		{
			if(prevDown)
			{
				m_PhysicalPrevPressed[_gameKey] = false;
				KeyEventHappened(View73::InputMethodKey::GKS_KeyUp,_gameKey,GetTimeForGameInput(_gameKey));
			}
		}
	}

	void GLKeyInputMethod::ResetPreviousPressed()
	{
		for( int i = 0 ; i < GIK_Num ; i++ )
		{
			m_PhysicalPrevPressed[i] = false;
		}
	}
}
