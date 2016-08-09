#include "View73ShaderEffect.h"

namespace View73
{
	//===============================================================================
	//ShaderEffectInstanceImpl Implementation
	class ShaderEffect::ShaderEffectInstanceImpl : public ShaderEffectInstance
	{
	private:
		
		ShaderEffect* m_ShaderEffect;

	public:
		ShaderEffectInstanceImpl(ShaderEffect* _effect)
			: ShaderEffectInstance()
			, m_ShaderEffect(_effect)
		{
			
		}

		~ShaderEffectInstanceImpl()
		{

		}

		virtual void BeginPass(unsigned short _passIndex)
		{
			m_ShaderEffect->BeginPass(_passIndex);
		}

		virtual void EndPass()
		{
			m_ShaderEffect->EndPass();
		}

		virtual unsigned short GetPassCount() const
		{
			return m_ShaderEffect->GetPassCount();
		}
	};

	//===============================================================================
	//ShaderEffect Implementation

	ShaderEffect::ShaderEffect()
	{

	}

	ShaderEffect::~ShaderEffect()
	{
		ClearAllPasses();
		ClearAllShaderEffectInstances();
		m_ActivePass.reset();
	}

	void ShaderEffect::ClearAllPasses()
	{
		unsigned short count = (unsigned short)m_AllPasses.size();

		for( int i = 0 ; i < count ; i++ )
		{
			BOOST_ASSERT_MSG( m_AllPasses[i].use_count() == 1, "Shader pass is still in use, first clear the reference used" );
			m_AllPasses[i].reset();
		}

		m_AllPasses.clear();
	}

	void ShaderEffect::ClearAllShaderEffectInstances()
	{
		unsigned short count = (unsigned short)m_AllEffectInstances.size();

		for( int i = 0 ; i < count ; i++ )
		{
			BOOST_ASSERT_MSG( m_AllEffectInstances[i].use_count() == 1, "Shader effect instance is still in use, first clear the reference used" );
			m_AllEffectInstances[i].reset();
		}

		m_AllEffectInstances.clear();
	}

	/*void ShaderEffect::AddShaderPass(unsigned int _passID, TSharedVertexProgramPtr _vertexProgram,TSharedFragmentProgramPtr _fragmentProgram)
	{
		unsigned short count = (unsigned short)m_AllPasses.size();

		BOOST_ASSERT_MSG( count < MAX_PASS_COUNT, 
			(String("Shader pass can't be more than ") + MAX_PASS_COUNT).CString() );

		if(count < MAX_PASS_COUNT)
		{
			TSharedShaderPassPtr pass(new ShaderPass(_vertexProgram,_fragmentProgram));
			m_AllPasses.push_back(pass);
		}
	}*/

	TSharedShaderEffectInstancePtr ShaderEffect::CreateShaderEffectInstance()
	{
		TSharedShaderEffectInstancePtr newEffectInstance(new ShaderEffectInstanceImpl(this));

		m_AllEffectInstances.push_back(newEffectInstance);

		return newEffectInstance;
	}

	void ShaderEffect::BeginPass(unsigned short _passIndex)
	{
		unsigned short count = (unsigned short)m_AllPasses.size();

		BOOST_ASSERT_MSG( _passIndex < count, (String("Pass index can't be more than and equal to") + count).CString() );
		BOOST_ASSERT_MSG( m_ActivePass == NULL,"Pass is already activated, please end the previous pass first");

		m_ActivePass = m_AllPasses[_passIndex];

		m_ActivePass->BeginPass();
		
	}

	void ShaderEffect::EndPass()
	{
		m_ActivePass->EndPass();
		m_ActivePass.reset();
	}
}
