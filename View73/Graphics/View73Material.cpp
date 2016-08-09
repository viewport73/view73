#include "View73Material.h"
#include "View73GlInclude.h"


namespace View73
{
	const Material Material::defaultMaterial = Material(String("defaultMaterial") );

	//===============================================================================
	Material::Material(const String& _matName)
		: m_MaterialName(_matName)
		, m_EnableCullFace(true)
		, m_FrontFace(GL_CCW)
		, m_CullFace(GL_BACK)
		, m_DepthTestEnabled(true)
		, m_GLShadeModel(GL_SMOOTH)
		, m_LightingEnabled(true)
		, m_AlphaTestEnable(false)
		, m_BlendingEnabled(false)
		, m_BlendingSFector(GL_SRC_ALPHA)
		, m_BlendingDFector(GL_ONE_MINUS_SRC_ALPHA)		
	{
	}
	
	Material::~Material()
	{
	}

	const String& Material::GetName() const
	{	
		return m_MaterialName;	
	}

	void Material::ApplyMaterial() const
	{
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

		EnableDisableGLProperty(GL_CULL_FACE,m_EnableCullFace);
		
		glFrontFace(m_FrontFace);
		glCullFace(m_CullFace);

		EnableDisableGLProperty(GL_ALPHA_TEST,m_AlphaTestEnable);

		EnableDisableGLProperty(GL_BLEND,m_BlendingEnabled);
		glBlendFunc(m_BlendingSFector, m_BlendingDFector);
		
		EnableDisableGLProperty(GL_DEPTH_TEST,m_DepthTestEnabled);

		glShadeModel(m_GLShadeModel);

		//glDisable(GL_DEPTH_WRITE);
		/*if(m_Texture != null)
		{
			glEnable(GL_TEXTURE_2D);

			glActiveTexture(GL_TEXTURE0);

			m_Texture.LoadTexture(gl, context);
			int textureID = m_Texture.GetTextureID();
			glBindTexture(GL_TEXTURE_2D,  textureID);

			m_Texture.ApplyTexture(gl);
		}
		else*/
		{
			EnableDisableGLProperty(GL_TEXTURE_2D,false);
		}

		EnableDisableGLProperty(GL_LIGHTING,m_LightingEnabled);
	}

	void Material::EnableDisableGLProperty(unsigned int _glProperty,bool _enable) const
	{
		if(_enable)
		{
			glEnable(_glProperty);
		}
		else
		{
			glDisable(_glProperty);
		}
	}
}