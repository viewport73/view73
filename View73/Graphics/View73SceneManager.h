/********************************************************************
	filename: 	View73SceneManager
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73SceneManager_h__
#define __View73SceneManager_h__

#include "../boost/smart_ptr.hpp"
#include "View73SceneNode.h"
#include <list>

namespace View73
{
	class SceneManager;
	typedef boost::shared_ptr<SceneManager> TSharedSceneManagerPtr;

	class SceneManager
	{
	public:

		typedef std::pair<SceneNode*,Renderable*> TRenderQueueItem;
		typedef std::list<TRenderQueueItem> TRenderQueue;
		
		typedef std::list<TSharedSceneNodePtr> TSharedSceneNodePtrList;

		typedef std::pair<SceneNode*,Light*> TSceneLight;
		typedef std::list<TSceneLight> TSceneLightList;

	protected:

		const String m_Name;

		TSharedSceneNodePtrList m_SceneNodesList;
		TSharedSceneNodePtr m_RootSceneNode;

	public:

		SceneManager(const String& _name);
		virtual ~SceneManager();

		inline TSharedSceneNodePtr GetRootSceneNode()	const {		return m_RootSceneNode;		}

		TSharedSceneNodePtr CreateSceneNode(const String& _name);
		TSharedSceneNodePtr GetSceneNode(const String& _name);
		
		TSharedSceneNodePtr CreateChildSceneNodeOfNode(TSharedSceneNodePtr _parent, const String& _childName);

		void DestroySceneNode(const String& _name);
		void ClearAllSceneNodes();

		inline const String& GetName() const		{	return m_Name;	}
		virtual void UpdateScene() = 0;
		virtual void RenderScene() = 0;

	private:

		virtual void PreDestroy(){};
		virtual void PostDestroy(){};
	};
}

#endif