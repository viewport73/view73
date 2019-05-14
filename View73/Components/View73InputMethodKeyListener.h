/********************************************************************
	filename: 	View73InputMethodKeyListener
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73InputMethodKeyListener_h__
#define __View73InputMethodKeyListener_h__

#include <boost/smart_ptr.hpp>

namespace View73
{
	class InputMethodKeyListener;
	typedef boost::shared_ptr<InputMethodKeyListener> TInputMethodKeyListenerSharedPtr;
	typedef boost::weak_ptr<InputMethodKeyListener> TInputMethodKeyListenerWeakPtr;
	typedef std::auto_ptr<InputMethodKeyListener> TInputMethodKeyListenerAutoPtr;

	class InputMethodKeyListener
	{
	public:
		InputMethodKeyListener(){}
		virtual ~InputMethodKeyListener(){}

		virtual bool OnKeyDown(unsigned long _gameKey) = 0;
		virtual bool OnKeyUp(unsigned long _gameKey) = 0;
		virtual bool OnKeyHeld(unsigned long _gameKey) = 0;
		virtual bool OnKeyPressed(unsigned long _gameKey) = 0;

	};
}

#endif