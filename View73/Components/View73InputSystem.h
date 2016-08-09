/********************************************************************
	filename: 	View73InputSystem
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73InputSystem_h__
#define __View73InputSystem_h__

#include "View73InputMethod.h"
#include <list>

namespace View73
{
	class InputSystem;
	typedef boost::shared_ptr<InputSystem> TInputSystemSharedPtr;
	//typedef boost::weak_ptr<InputSystem> TInputSystemWeakPtr;
	typedef std::auto_ptr<InputSystem> TInputSystemAutoPtr;

	class InputSystem
	{
	public:

		typedef std::list<TInputMethodSharedPtr> TInputMethodSharedPtrList;

	protected:

		TInputMethodSharedPtrList m_AllInputMethods;

		void UpdateAllInputMethods(const FrameEvent& _frameEvent);

	public:

		InputSystem();
		virtual ~InputSystem();

		TInputMethodSharedPtr AddInputMethod(TInputMethodAutoPtr _newIpMethod);
		void ClearAllInputMethods();

		virtual void Update(const FrameEvent& _frameEvent) = 0;
	};
}

#endif