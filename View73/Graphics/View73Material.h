/********************************************************************
	filename: 	View73Material
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Material_h__
#define __View73Material_h__

#include "../Utils/View73String.h"
#include <boost/smart_ptr.hpp>
#include "View73ShaderEffectInstance.h"

namespace View73
{
	class Material;

	typedef boost::shared_ptr<Material> TSharedMaterialPtr;

	class Material
	{
	public:

		static const Material defaultMaterial;

	private:
		
		const String			m_MaterialName;
		//Colour				m_AmbientColour;
		//Colour				m_DiffuseColour;
		bool					m_EnableCullFace;
		unsigned int			m_FrontFace;
		unsigned int			m_CullFace;
		bool					m_DepthTestEnabled;
		unsigned int			m_GLShadeModel;
		bool					m_LightingEnabled;
		bool					m_AlphaTestEnable;
		bool					m_BlendingEnabled;
		unsigned int			m_BlendingSFector;
		unsigned int			m_BlendingDFector;

		TSharedShaderEffectInstancePtr m_ShaderEffect;

		void EnableDisableGLProperty(unsigned int _glProperty,bool _enable) const;

	public:
		Material(const String& _matName);
		~Material();

		const String& GetName() const;

		void ApplyMaterial() const;

		inline void SetShaderEffect(TSharedShaderEffectInstancePtr _effect) {	m_ShaderEffect = _effect;		}

		inline void SetLightingEnabled(bool _enabled)						{	m_LightingEnabled = _enabled;	}
	};
}

#endif