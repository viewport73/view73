#include "View73ShaderPass.h"

namespace View73
{
	ShaderPass::ShaderPass(TSharedVertexProgramPtr _vertexProgram,TSharedFragmentProgramPtr  _fragmentProgram)
		: m_VertexProgram(_vertexProgram)
		, m_FragmentProgram(_fragmentProgram)
		, m_ProgramObject(0)
		, m_Linked(false)
	{
		Create();
	}

	ShaderPass::~ShaderPass()
	{
		Destroy();
	}

	void ShaderPass::Create()
	{
		m_ProgramObject = glCreateProgram();
	}

	void ShaderPass::Destroy()
	{
		DetachAllShaders();

		m_VertexProgram.reset();
		m_FragmentProgram.reset();

		glDeleteShader(m_ProgramObject);
	}

	void ShaderPass::DetachAllShaders()
	{
		glDetachShader(m_ProgramObject, m_VertexProgram->GetShaderObject());
		CHECK_GL_ERROR();

		glDetachShader(m_ProgramObject, m_FragmentProgram->GetShaderObject());
		CHECK_GL_ERROR();
	}

	void ShaderPass::AttachAllShaders()
	{
		glAttachShader(m_ProgramObject, m_VertexProgram->GetShaderObject());
		CHECK_GL_ERROR();

		glAttachShader(m_ProgramObject, m_FragmentProgram->GetShaderObject());
		CHECK_GL_ERROR();
	}

	bool ShaderPass::Link()
	{
//		unsigned int i;

		if (m_Linked) 
		{
			DetachAllShaders();
		}

		AttachAllShaders();

		GLint linked; 
		glLinkProgram(m_ProgramObject);
		CHECK_GL_ERROR();
		glGetProgramiv(m_ProgramObject, GL_LINK_STATUS, &linked);
		CHECK_GL_ERROR();

		if (linked)
		{
			m_Linked = true;
			return true;
		}
		else
		{
			gLogManager->WriteLog("Unable to Link Shader");
		}

		return false;
	}

	//-----------------------------------------------------------------------------
	void ShaderPass::BindAttribLocation(GLint index, GLchar* name)
	{
		glBindAttribLocation(m_ProgramObject, index, name);
	}

	void ShaderPass::BeginPass()
	{
		if (m_Linked)
		{
			glUseProgram(m_ProgramObject);
			CHECK_GL_ERROR();
		}
	}

	void ShaderPass::EndPass()
	{
		glUseProgram(0);
		CHECK_GL_ERROR();
	}
}
