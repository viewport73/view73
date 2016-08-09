#include "View73Overlay.h"

namespace View73
{
	Overlay::Overlay(const String& _name)
			: Renderable()
			, m_Name(_name)
			, m_OverlayMesh( new Mesh(_name + "_Mesh"))
			, m_Visible(true)
	{
	}

	Overlay::~Overlay()
	{
		m_OverlayMesh.reset();
		m_OverlayMaterial.reset();
	}

	void Overlay::Render()
	{
		if(m_EnablePreRenderUpdate == true)
		{
			PreRenderUpdate();
		}
		
		if(m_Visible == true)
		{			
			if(m_OverlayMaterial != NULL)
			{
				ApplyMaterial(m_OverlayMaterial);
			}
			else
			{
				//ApplyMaterial(Material::defaultMaterial);
			}
			
			m_OverlayMesh->Render();
		}
	}

	void Overlay::ApplyMaterial(TSharedMaterialPtr _material)
	{
	}
}