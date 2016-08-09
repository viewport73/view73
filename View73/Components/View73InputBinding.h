/********************************************************************
	filename: 	View73InputBinding
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73InputBinding_h__
#define __View73InputBinding_h__

#include "../boost/smart_ptr.hpp"

namespace View73
{
	class InputBinding;

	typedef boost::shared_ptr<InputBinding> TInputBindingSharedPtr;
	typedef std::auto_ptr<InputBinding> TInputBindingAutoPtr;

	class InputBinding
	{
	public:
		InputBinding()
		{
		}

		virtual ~InputBinding()
		{
		}

		virtual int GetGameInputFromPhysicalKey(int _key) = 0;
		virtual int GetPhysicalKeyFromGameInput(int _gameInput) = 0;
		virtual float GetTimeForGameInput(int _gameInput) = 0;
	};
}

#endif