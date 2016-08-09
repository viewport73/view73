#include "View73OverlayScreen.h"

namespace View73
{
	OverlayScreen::OverlayScreen(const String& _name,const Rect& _rect)
		: Overlay(_name)
		, m_ImageRect(_rect)
		, m_DirtyImageRect(true)
	{
		Construct();
	}

	OverlayScreen::~OverlayScreen()
	{
	}

	void OverlayScreen::PreRenderUpdate()
	{
	}

	void OverlayScreen::Construct()
	{
		float vertices[] = {
				m_ImageRect.m_Left	, m_ImageRect.m_Top		, 0.0f,
				m_ImageRect.m_Right	, m_ImageRect.m_Top		, 0.0f,
				m_ImageRect.m_Right	, m_ImageRect.m_Bottom	, 0.0f,
				m_ImageRect.m_Left	, m_ImageRect.m_Bottom	, 0.0f,
			};

		unsigned int indices[] = {
					2,1,0,
					3,2,0,
					};
		
		m_OverlayMesh->Lock();
		/*int texWidth;
		int texHeight;
		
		float[] texCoords = {
								(float)m_ImageRect.m_Left/(float)texWidth , (float)m_ImageRect.m_Top/(float)texHeight,
								(float)m_ImageRect.m_Right/(float)texWidth , (float)m_ImageRect.m_Top/(float)texHeight,
								(float)m_ImageRect.m_Right/(float)texWidth , (float)m_ImageRect.m_Bottom/(float)texHeight,
								(float)m_ImageRect.m_Left/(float)texWidth , (float)m_ImageRect.m_Bottom/(float)texHeight,
								
								
							};
		
		m_OverlayMesh.SetTexCoords(texCoords, (short)texCoords.length);*/

		
		m_OverlayMesh->SetVertexBuffer(vertices, 12);
		m_OverlayMesh->SetIndexBuffer(indices, 6);

		m_OverlayMesh->Unlock();
	}
}