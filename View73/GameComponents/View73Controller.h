/********************************************************************
	filename: 	View73Controller
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Controller_h__
#define __View73Controller_h__

#include <boost/smart_ptr.hpp>
#include "../Graphics/View73FrameEvent.h"

namespace View73
{
	class Controller;

	typedef boost::shared_ptr<Controller> TControllerSharedPtr;
	typedef boost::weak_ptr<Controller> TControllerWeakPtr;

	class Controller
	{
	public:

		Controller(){}
		virtual ~Controller(){}

		virtual bool CanRemoveController() const	= 0;
		virtual void Update(const FrameEvent& _frameEvent) = 0;
	};
}

#endif