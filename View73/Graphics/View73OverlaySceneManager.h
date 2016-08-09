/********************************************************************
	filename: 	View73OverlaySceneManager
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73OverlaySceneManager_h__
#define __View73OverlaySceneManager_h__

#include "View73SceneManager.h"
#include "View73OverlayScreen.h"
#include <list>

namespace View73
{
	class OverlaySceneManager : public SceneManager
	{
	public:
		
		typedef std::list<TOverlaySharedPtr> TOverlayPtrList;

	private:

		static const String m_ClassName;

		TOverlayPtrList m_AllOverlays;
		TRenderQueue m_RenderQueue;

	public:

		static const String& GetClassType()	{	return m_ClassName;		}
		static void RegisterTravelClass();
	
		OverlaySceneManager(const String& _name);
		virtual ~OverlaySceneManager();

		TOverlaySharedPtr AddOverlay(TOverlayAutoPtr _overlay);
		void RemoveOverlay(TOverlayAutoPtr _overlay);

	protected:

		virtual void UpdateScene();
		virtual void RenderScene();

		void ResetRenderQueue();

	private:
		
		void GenerateRenderQueue();
		void RenderInternal(const Matrix44& _mat,Renderable* _renderable);

		void ClearAllOverlays();
		virtual void PreDestroy();
		virtual void PostDestroy();

	};
}

#endif