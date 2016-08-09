/********************************************************************
	filename: 	View73OverlayFrustrum
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73OverlayFrustrum_h__
#define __View73OverlayFrustrum_h__

#include "View73Frustrum.h"

namespace View73
{
	class OverlayFrustrum : public Frustrum
	{
	private:

	public:

		OverlayFrustrum(const String& _name, ProjectionType _type,TSharedSceneManagerPtr _sceneManager);
		virtual ~OverlayFrustrum();

	private:

		virtual void OnRenderStart();
		virtual void OnRenderEnd();

	public:

		static TCameraCreationFunction GetCreationFunction();
	};
}

#endif