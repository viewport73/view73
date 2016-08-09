/********************************************************************
	filename: 	View73BasicSceneManager
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73BasicSceneManager_h__
#define __View73BasicSceneManager_h__

#include "View73SceneManager.h"
#include "View73Renderable.h"

namespace View73
{
	class BasicSceneManager : public SceneManager
	{
	private:

		static const String m_ClassName;
		
		TRenderQueue m_RenderQueue;
		TSceneLightList m_SceneLights;

	public:

		static const String& GetClassType()	{	return m_ClassName;		}
		static void RegisterTravelClass();
	
		BasicSceneManager(const String& _name);
		virtual ~BasicSceneManager();

	protected:

		void ResetRenderQueue();
		void ResetLightList();

		void ApplySceneLights();
		void ApplySceneLight(const Matrix44& _mat,Light* _light);

		virtual void UpdateScene();
		virtual void RenderScene();

	private:

		void UpdateSceneHierarchy(SceneNode* _parent);
		void AddItemsToRenderQueueFromSceneNode(SceneNode* _node);
		void RenderInternal(const Matrix44& _mat,Renderable* _renderable);
		virtual void PreDestroy(){}
		virtual void PostDestroy(){}
	};
}

#endif