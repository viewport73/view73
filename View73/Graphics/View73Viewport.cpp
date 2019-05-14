#include "View73Viewport.h"
#include "View73GlInclude.h"

namespace View73
{
	Viewport::Viewport(const String& _name, unsigned int _left , unsigned int _bottom , unsigned int _width , unsigned int _height)
		: m_Name(_name)
		, m_DirtyAspectRatio(true)
		, m_ClearColour(Colour(1,1,0,0))
	{
		SetViewport(_left,_bottom,_width,_height);
	}

	Viewport::~Viewport()
	{
		ClearAllCameras();
	}

	void Viewport::SetViewport(unsigned int _left , unsigned int _bottom , unsigned int _width , unsigned int _height)
	{
		m_Left = _left;
		m_Bottom = _bottom;
		m_Width = _width;
		m_Height = _height;

		m_DirtyAspectRatio = true;
	}

	TSharedFrustrumPtr Viewport::CreateCamera(TCameraCreationFunction _fun,const String& _name
					, Frustrum::ProjectionType _projType,TSharedSceneManagerPtr _sceneManager)
	{
		TSharedFrustrumPtr camera = GetCamera(_name);

		if(camera == NULL)
		{
			camera = _fun(_name,_projType,_sceneManager);

			m_CameraList.push_back(camera);

			float ratio =  (float)m_Width/(float)m_Height;
			camera->SetViewportAspectRatio(ratio);
		}

		return camera;
	}

	TSharedFrustrumPtr Viewport::GetCamera(const String& _name)
	{
		TSharedFrustrumList::iterator itr = m_CameraList.begin();
		TSharedFrustrumList::iterator end = m_CameraList.end();

		TSharedFrustrumPtr found;

		for( ; itr != end ; itr++ )
		{
			if((*itr)->GetName() == _name )
			{
				found = (*itr);
				break;
			}
		}

		return found;
	}

	void Viewport::DestroyCamera(const String& _name)
	{
		TSharedFrustrumList::iterator itr = m_CameraList.begin();
		TSharedFrustrumList::iterator end = m_CameraList.end();

		TSharedFrustrumPtr found;

		for( ; itr != end ; itr++ )
		{
			if((*itr)->GetName() == _name )
			{
				found = (*itr);
				itr = m_CameraList.erase(itr);
				break;
			}
		}

		BOOST_ASSERT_MSG(found.use_count() == 1 , (String("Camera named ") + found->GetName() 
					+ String(" could not be deleted still in use, but removed from list, may have memory leaks") ).CString() );

		found.reset();
	}

	void Viewport::ClearAllCameras()
	{
		TSharedFrustrumList::iterator itr = m_CameraList.begin();
		TSharedFrustrumList::iterator end = m_CameraList.end();

		for( ; itr != end ; itr++ )
		{
			BOOST_ASSERT_MSG((*itr).use_count() == 1 , (String("Camera named ") + (*itr)->GetName() 
				+ String(" could not be deleted still in use, but removed from list, may have memory leaks") ).CString() );
			(*itr).reset();
		}

		m_CameraList.clear();
	}

	void Viewport::UpdateViewport()
	{
		UpdateAspectRatio();
		UpdateFrustrums();
	}

	void Viewport::RenderScene()
	{
		TSharedFrustrumList::iterator itr = m_CameraList.begin();
		TSharedFrustrumList::iterator end = m_CameraList.end();

		TSharedFrustrumPtr found;

		SetViewport();
		for( ; itr != end ; itr++ )
		{
			(*itr)->RenderScene();

			glClear(GL_DEPTH_BUFFER_BIT);
			glFlush();	
		}
	}

	void Viewport::UpdateAspectRatio()
	{
		if(m_DirtyAspectRatio)
		{
			TSharedFrustrumList::iterator itr = m_CameraList.begin();
			TSharedFrustrumList::iterator end = m_CameraList.end();

			TSharedFrustrumPtr found;

			float ratio =  (float)m_Width/(float)m_Height;
			
			for( ; itr != end ; itr++ )
			{
				(*itr)->SetViewportAspectRatio(ratio);
				(*itr)->UpdateScene();
			}
		}
		m_DirtyAspectRatio = false;
	}
	
	void Viewport::UpdateFrustrums()
	{
		TSharedFrustrumList::iterator itr = m_CameraList.begin();
		TSharedFrustrumList::iterator end = m_CameraList.end();

		TSharedFrustrumPtr found;
		
		for( ; itr != end ; itr++ )
		{
			(*itr)->UpdateScene();
		}
	}

	void Viewport::SetViewport()
	{
		//set the viewport
		glViewport(m_Left, m_Bottom, m_Width, m_Height);
		glScissor(m_Left, m_Bottom, m_Width, m_Height);
		
		glClearColor(m_ClearColour.r,m_ClearColour.g, m_ClearColour.b,m_ClearColour.a);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
		glFlush ();	
	}
}