/********************************************************************
	filename: 	View73SceneNode
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73SceneNode_h__
#define __View73SceneNode_h__

#include "View73Node.h"
#include "View73Renderable.h"
#include "View73Light.h"
#include <list>
#include <vector>

namespace View73
{
	class SceneNode;

	typedef boost::shared_ptr<SceneNode> TSharedSceneNodePtr;
	typedef std::list<TSharedSceneNodePtr> TSceneNodesList;
	typedef std::vector<TSharedSceneNodePtr> TSceneNodesArray;

	class SceneNode : public Node
	{
	private:
		
		TRenderablesList m_AllRenderables;
		TLightList m_AllLights;
		bool m_Visible;
		
	public:

		SceneNode(const String& _nodeName, bool _overrideParentTransforms = false);
		virtual ~SceneNode();

		void AddRenderable(TSharedRenderablePtr _renderable);
		void AddLight(TSharedLightPtr _light);
		const TRenderablesList& GetRenderablesList() const	{	return m_AllRenderables;	}
		const TLightList& GetLightList() const				{	return m_AllLights;			}
		inline void SetVisible(bool _visible)				{	m_Visible = _visible;		}
		inline bool GetVisible() const						{	return m_Visible;			}

	private:

		void ClearAllRenderables();
		void ClearAllLights();

		virtual void UpdateFromParent();
		virtual void TransformsUpdated();
	};
}

#endif