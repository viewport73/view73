/********************************************************************
	filename: 	View73OnRenderListener
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73OnRenderListener_h__
#define __View73OnRenderListener_h__

#include <boost/smart_ptr.hpp>
#include <list>
#include "View73Renderable.h"

namespace View73
{
	class OnRenderListener;
	
	typedef boost::shared_ptr<OnRenderListener> TOnRenderListenerSharedPtr;
	typedef boost::weak_ptr<OnRenderListener> TOnRenderListenerWeakPtr;

	typedef std::list<TOnRenderListenerWeakPtr> TOnRenderListenerWeakPtrList;

	class OnRenderListener
	{
	public:
		OnRenderListener(){}
		virtual ~OnRenderListener(){}

		virtual void OnRender(TSharedRenderablePtr _renderable) = 0;
		virtual void OnRenderFinished() = 0;
	};
}

#endif