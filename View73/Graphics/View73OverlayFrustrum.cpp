#include "View73OverlayFrustrum.h"
#include <boost/bind.hpp>
#include "View73GlInclude.h"

View73::TSharedFrustrumPtr CreateCamera(const View73::String& _name, View73::Frustrum::ProjectionType _projType
		,View73::TSharedSceneManagerPtr _sceneManager)
{
	View73::TSharedFrustrumPtr newCamera(new View73::OverlayFrustrum(_name,_projType,_sceneManager));
	return newCamera;
}

namespace View73
{
	OverlayFrustrum::OverlayFrustrum(const String& _name, ProjectionType _type,TSharedSceneManagerPtr _sceneManager)
		: Frustrum(_name,_type,_sceneManager)
	{
		//SetCustomProjeParams(0,_screenWidth,0,_screenHeight);
		SetNearClipDistance(-1.0f);
		SetFarClipDistance(1.0f);
	}

	OverlayFrustrum::~OverlayFrustrum()
	{
	}

	void OverlayFrustrum::OnRenderStart()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void OverlayFrustrum::OnRenderEnd()
	{
	}

	TCameraCreationFunction OverlayFrustrum::GetCreationFunction()
	{
		return boost::bind(CreateCamera,_1,_2,_3);
	}
}