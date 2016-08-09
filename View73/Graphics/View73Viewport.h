/********************************************************************
	filename: 	View73Viewport
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Viewport_h__
#define __View73Viewport_h__

#include "../boost/smart_ptr.hpp"
#include "View73Colour.h"
#include <list>
#include "View73Camera.h"
#include "View73SceneManager.h"

namespace View73
{
	class Viewport;
	typedef boost::shared_ptr<Viewport> TSharedViewportPtr;

	class Viewport
	{
	public:

		typedef std::list<TSharedFrustrumPtr> TSharedFrustrumList;

	private:

		const String m_Name;
		unsigned int m_Left;
		unsigned int m_Bottom;
		unsigned int m_Width;
		unsigned int m_Height;
		Colour m_ClearColour;

		TSharedFrustrumList m_CameraList;
		bool m_DirtyAspectRatio;

	public:
		
		Viewport( const String& _name, unsigned int _left , unsigned int _bottom , unsigned int _width , unsigned int _height);
		virtual ~Viewport();

		void SetViewport(unsigned int _left , unsigned int _bottom , unsigned int _width , unsigned int _height);

		TSharedFrustrumPtr CreateCamera(TCameraCreationFunction _fun,const String& _name, Frustrum::ProjectionType _projType,TSharedSceneManagerPtr _sceneManager);
		TSharedFrustrumPtr GetCamera(const String& _name);
		void DestroyCamera(const String& _name);
		void ClearAllCameras();

		const String& GetName() const	{	return m_Name;	}

		virtual void UpdateViewport();
		virtual void RenderScene();

	private:

		void UpdateAspectRatio();
		void UpdateFrustrums();
		void SetViewport();
	};
};

#endif