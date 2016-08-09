#include "View73VertexProgram.h"

namespace View73
{
	VertexProgram::VertexProgram(const String& _filename)
		: ShaderProgram(ShaderProgram::SPT_Vertex,_filename)
	{
		//if (useGLSL)
		{
			m_GLShaderObject = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
			CHECK_GL_ERROR();
		}
	}

	VertexProgram::~VertexProgram()
	{

	}
}