/********************************************************************
	filename: 	View73InputMethod
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73InputMethod_h__
#define __View73InputMethod_h__


#include "View73InputBinding.h"
#include "../Graphics/View73FrameEvent.h"

namespace View73
{
	class InputMethod;
	typedef boost::shared_ptr<InputMethod> TInputMethodSharedPtr;
	//typedef boost::weak_ptr<InputMethod> TInputMethodWeakPtr;
	typedef std::auto_ptr<InputMethod> TInputMethodAutoPtr;

	class InputMethod
	{
	protected:
	
		TInputBindingSharedPtr m_InputBinding;

	public:
		InputMethod(TInputBindingAutoPtr _inputBinding)
			: m_InputBinding(_inputBinding.release())
		{
		}

		virtual ~InputMethod()
		{
			BOOST_ASSERT_MSG(m_InputBinding.use_count() == 1, "InputBinding is already in use, first clear all references" );
			m_InputBinding.reset();
		}

		//it will release the previous input binding
		void SetInputBinding(TInputBindingAutoPtr _inputBinding)
		{
			BOOST_ASSERT_MSG(m_InputBinding.use_count() == 1, "InputBinding is already in use, first clear all references" );
			m_InputBinding.reset(_inputBinding.release());
		}

		int GetGameInputFromPhysicalKey(int _key) 
		{
			BOOST_ASSERT_MSG(m_InputBinding.use_count() != 0, "Doesn't have a binding" );
			return m_InputBinding->GetGameInputFromPhysicalKey(_key);
		}

		int GetPhysicalKeyFromGameInput(int _gameInput)
		{
			BOOST_ASSERT_MSG(m_InputBinding.use_count() != 0, "Doesn't have a binding" );
			return m_InputBinding->GetPhysicalKeyFromGameInput(_gameInput);
		}

		float GetTimeForGameInput(int _gameInput)
		{
			BOOST_ASSERT_MSG(m_InputBinding.use_count() != 0, "Doesn't have a binding" );
			return m_InputBinding->GetTimeForGameInput(_gameInput);
		}

		virtual void Update(const FrameEvent& _frameEvent) = 0;
	};
}

#endif