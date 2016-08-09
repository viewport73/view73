#include "View73FragmentProgram.h"

namespace View73
{
	FragmentProgram::FragmentProgram(const String& _filename)
		: ShaderProgram(ShaderProgram::SPT_Fragment,_filename)
	{
		//if (useGLSL)
		{
			m_GLShaderObject = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB); 
			CHECK_GL_ERROR();
		}
	}

	FragmentProgram::~FragmentProgram()
	{

	}
}