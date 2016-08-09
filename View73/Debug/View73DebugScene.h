/********************************************************************
	filename: 	View73DebugScene
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73DebugScene_h__
#define __View73DebugScene_h__

#include "../Graphics/View73OnRenderListener.h"
#include "View73DebugObject.h"
#include "../Graphics/View73Material.h"

namespace View73
{
	class DebugScene;

	typedef boost::shared_ptr<DebugScene> TSharedDebugScenePtr;
	typedef boost::weak_ptr<DebugScene> TDebugSceneWeakPtr;

	class DebugScene : public View73::OnRenderListener
	{
	protected:

		
		TSharedDebugDrawerPtr m_DebugDrawer;
		TTSharedDebugObjectPtrList m_AllDebugObjects;

		TFrustrumWeakPtr m_FrustrumPtr;

		TSharedMaterialPtr m_DebugSceneMaterial;
		

	public:

		DebugScene(TDebugDrawerAutoPtr _debugDrawer, TFrustrumWeakPtr _frustrumPtr);
		virtual ~DebugScene();

		virtual void OnRender(TSharedRenderablePtr){}
		virtual void OnRenderFinished();

		void AddDebugObject(TDebugObjectAutoPtr _debugObject);

	protected:

		void Destroy();
	};
}

#endif