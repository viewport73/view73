/********************************************************************
	filename: 	View73InputMethodAxis
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73InputMethodAxis_h__
#define __View73InputMethodAxis_h__

#include "View73InputMethod.h"
#include "../Math/View73Vector2.h"

namespace View73
{
	class InputMethodAxis;
	typedef boost::shared_ptr<InputMethodAxis> TInputMethodAxisSharedPtr;
	typedef boost::weak_ptr<InputMethodAxis> TInputMethodAxisWeakPtr;
	typedef std::auto_ptr<InputMethodAxis> TInputMethodAxisAutoPtr;

	class InputMethodAxis : public InputMethod
	{
	protected:

		Vector2 m_AxisValue;

	public:

		InputMethodAxis(TInputBindingAutoPtr _inputBinding)
			: InputMethod(_inputBinding)
			, m_AxisValue(Vector2::ZERO)
		{
		}

		virtual ~InputMethodAxis()
		{
		}

		inline const Vector2& GetAxisValue() const		{	return m_AxisValue;	}

	private:

		virtual void Update(const FrameEvent& _frameEvent) = 0;
	};
}

#endif