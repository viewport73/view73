/********************************************************************
	filename: 	View73Overlay
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Overlay_h__
#define __View73Overlay_h__

#include "View73Renderable.h"
#include "View73Mesh.h"
#include "View73Material.h"
#include <boost/smart_ptr.hpp>

namespace View73
{
	class Overlay;

	typedef boost::shared_ptr<Overlay> TOverlaySharedPtr;
	//typedef boost::weak_ptr<Overlay> TOverlayWeakPtr;
	typedef std::auto_ptr<Overlay> TOverlayAutoPtr;

	class Overlay : public Renderable
	{
	private:

		bool m_EnablePreRenderUpdate;
		int m_ZOrder;
		bool m_Visible;
		const String m_Name;

	protected:

		TSharedMaterialPtr m_OverlayMaterial;
		TSharedMeshPtr m_OverlayMesh;

	public:

		Overlay(const String& _name);
		virtual ~Overlay();
	
		void SetMaterial(TSharedMaterialPtr _material)	{	m_OverlayMaterial = _material;		}
		void SetZOrder(int _zOrder)						{	m_ZOrder = _zOrder;					}
	
		int GetZOrder()									{	return m_ZOrder;					}
		inline const String& GetName() const		{	return m_Name;						}
	
		void SetEnablePreRenderUpdate(bool _enable)		{	m_EnablePreRenderUpdate = _enable;	}
	
		void Render();

	private:

		virtual void PreRenderUpdate() = 0;

		void ApplyMaterial(TSharedMaterialPtr _material);

	};
}

#endif