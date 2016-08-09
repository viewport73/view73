/********************************************************************
	filename: 	View73OverlayScreen
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73OverlayScreen_h__
#define __View73OverlayScreen_h__

#include "View73Overlay.h"
#include "../Math/View73Rect.h"

namespace View73
{
	class OverlayScreen : public Overlay
	{
	private:

		Rect m_ImageRect;
		bool m_DirtyImageRect;

	public:

		OverlayScreen(const String& _name,const Rect& _rect);
		virtual ~OverlayScreen();

	private:

		void Construct();

		virtual void PreRenderUpdate();
	};
}

#endif