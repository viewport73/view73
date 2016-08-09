/********************************************************************
	filename: 	View73Renderable
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Renderable_h__
#define __View73Renderable_h__

#include "../boost/smart_ptr.hpp"
#include <list>

namespace View73
{
	class Renderable;
	typedef boost::shared_ptr<Renderable> TSharedRenderablePtr;
	typedef std::list<TSharedRenderablePtr> TRenderablesList;

	class Renderable
	{
	public:
		Renderable(){}
		virtual ~Renderable(){}
		virtual void Render() = 0;
	};
}

#endif