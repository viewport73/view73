#include "View73BasicSceneManager.h"
#include "View73GraphicsRoot.h"
#include "View73GlInclude.h"
#include "../Utils/View73String.h"

namespace
{
	static View73::TSharedSceneManagerPtr CreateBasicSceneManager(const View73::String& _name)
	{
		View73::TSharedSceneManagerPtr scnMgr(new View73::BasicSceneManager(_name));
		return scnMgr;
	}
}

namespace View73
{
	const String BasicSceneManager::m_ClassName = String("BasicSceneManager");

	BasicSceneManager::BasicSceneManager(const String& _name)
		: SceneManager(_name)
	{
	}

	BasicSceneManager::~BasicSceneManager()
	{
		ResetRenderQueue();
		ResetLightList();
	}

	void BasicSceneManager::RegisterTravelClass()
	{
		gGraphicsRoot->RegisterClassCreator(GetClassType(), &CreateBasicSceneManager);
	}

	void BasicSceneManager::ResetRenderQueue()
	{
		m_RenderQueue.clear();
	}

	void BasicSceneManager::ResetLightList()
	{
		m_SceneLights.clear();
	}

	void BasicSceneManager::UpdateScene()
	{
		ResetRenderQueue();
		ResetLightList();
		UpdateSceneHierarchy(m_RootSceneNode.get());
	}

	void BasicSceneManager::RenderScene()
	{
		ApplySceneLights();

		TRenderQueue::iterator itr = m_RenderQueue.begin();
		TRenderQueue::iterator end = m_RenderQueue.end();

		for( ; itr != end ; itr++ )
		{
			if( (*itr).first->GetVisible() )
			{
				const Matrix44& _transform = (*itr).first->GetWorldTransform();
				RenderInternal(_transform,(*itr).second);
			}
		}
	}

	void BasicSceneManager::RenderInternal(const Matrix44& _mat,Renderable* _renderable)
	{
		float matrix[16];
		        
		int p = 0;
		for(int i = 0 ; i < 4 ; i++)
		{
			for(int j = 0 ; j < 4 ; j++)
			{
				matrix[p] = _mat[j][i];
				p++;
			}
		}

		glPushMatrix();
			glMultMatrixf(matrix);
			_renderable->Render();
		glPopMatrix();
	}

	//proper algorithms has to be implemented for generating render queue
	void BasicSceneManager::UpdateSceneHierarchy(SceneNode* _parent)
	{
		if( _parent->GetVisible() )
		{
			_parent->Update();
			if( _parent->IsNodeOfType(Node::eNT_SceneNode) )
			{
				AddItemsToRenderQueueFromSceneNode(_parent);
			}

			const TWeakNodePtrList& childsList = _parent->GetChildList();
			TWeakNodePtrList::const_iterator itr = childsList.begin();

			while( itr != childsList.end() )
			{
				TSharedNodePtr child = (*itr).lock();
				UpdateSceneHierarchy(static_cast<SceneNode*>(child.get()) );
			
				itr++;
			}
		}
	}

	void BasicSceneManager::AddItemsToRenderQueueFromSceneNode(SceneNode* _node)
	{
		//need to sort the queue based on bounding boxes.... 
		//will do later when descent scene will come to game
		const TRenderablesList& currList = _node->GetRenderablesList();
		TRenderablesList::const_iterator renItr = currList.begin();
		TRenderablesList::const_iterator renEnd = currList.end();

		for( ; renItr != renEnd ; renItr++ )
		{
			m_RenderQueue.push_back(TRenderQueueItem(_node,(*renItr).get()));
		}

		const TLightList& currLights = _node->GetLightList();
		TLightList::const_iterator ltItr = currLights.begin();
		TLightList::const_iterator ltEnd = currLights.end();

		for( ; ltItr != ltEnd ; ltItr++ )
		{
			m_SceneLights.push_back(TSceneLight(_node,(*ltItr).get()));
		}
	}

	void BasicSceneManager::ApplySceneLights()
	{
		TSceneLightList::iterator itr = m_SceneLights.begin();
		TSceneLightList::iterator end = m_SceneLights.end();

		//for( ; itr != end ; itr++ )
		{
			if( (*itr).first->GetVisible() )
			{
				const Matrix44& _transform = (*itr).first->GetWorldTransform();
				ApplySceneLight(_transform,(*itr).second);
			}
		}
	}

	void BasicSceneManager::ApplySceneLight(const Matrix44& _mat,Light* _light)
	{
		float matrix[16];

		int p = 0;
		for(int i = 0 ; i < 4 ; i++)
		{
			for(int j = 0 ; j < 4 ; j++)
			{
				matrix[p] = _mat[j][i];
				p++;
			}
		}

		glPushMatrix();
			//glMultMatrixf(matrix);
			_light->ApplyLight(GL_LIGHT0);
		glPopMatrix();
	}
}