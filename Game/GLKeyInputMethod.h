/********************************************************************
	filename: 	GLKeyInputMethod
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __GLKeyInputMethod_h__
#define __GLKeyInputMethod_h__

#include "../View73/Components/View73InputMethodKey.h"
#include "../NeHeGL.h"
#include "../boost/smart_ptr.hpp"
#include "GameInputKeys.h"

namespace Game
{
	
	class GLKeyInputMethod : public View73::InputMethodKey
	{
	private:

		Keys* m_Keys;

		bool m_PhysicalPrevPressed[GIK_Num];

	public:

		GLKeyInputMethod(View73::TInputBindingAutoPtr _inputBinding,Keys* _keys);
		virtual ~GLKeyInputMethod();

		virtual void Update(const View73::FrameEvent& _frameEvent);

	private:

		void ResetPreviousPressed();
		void UpdateGameKey(int _gameKey);
	};
}

#endif