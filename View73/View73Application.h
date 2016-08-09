/********************************************************************
	filename: 	View73Application
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Application_h__
#define __View73Application_h__

#include <boost/smart_ptr.hpp>
#include "Graphics/View73FrameEvent.h"

namespace View73
{
	class Application;

	typedef boost::shared_ptr<Application> TSharedApplicationPtr;
	typedef std::auto_ptr<Application> TApplicationAutoPtr;

	class Application
	{
	public:

		Application(){}
		virtual ~Application(){}

		virtual void WindowSizeChanged(float _newWidth, float _newHeight) = 0;

		//called before update call
		//if returns false application will quit...
		virtual bool PreUpdate() = 0;

		//Called before render call
		virtual void Update(const FrameEvent& _event) = 0;
	};
}

#endif