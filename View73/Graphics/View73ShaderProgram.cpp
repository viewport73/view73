#include "View73ShaderProgram.h"
#include "../Utils/View73File.h"
#include "../Utils/View73CharacterUtils.h"

namespace
{
	using namespace View73;

	//-----------------------------------------------------------------------------
	// Error, Warning and Info Strings
/*	const char* const aGLSLStrings[] = {
		"[e00] GLSL is not available!",
		"[e01] Not a valid program object!",
		"[e02] Not a valid object!",
		"[e03] Out of memory!",
		"[e04] Unknown compiler error!",
		"[e05] Linker log is not available!",
		"[e06] Compiler log is not available!",
		"[Empty]"
	};*/
	//-----------------------------------------------------------------------------      
}

namespace View73
{
	ShaderProgram::ShaderProgram(ShaderProgramType _shaderType,const String& _filename)
		: m_FileName(_filename)
		, m_ShaderType(_shaderType)
		, m_Loaded(false)
		, m_Compiled(false)
		, m_ProgramName(GetProgramNameFromFilename(_filename))
	{

	}

	ShaderProgram::~ShaderProgram()
	{
		Destroy();
	}

	void ShaderProgram::Destroy()
	{
		if (m_Compiled)
		{ 
			m_Loaded = false;
			m_Compiled = false;
			glDeleteObjectARB(m_GLShaderObject);
			//TODO: Check GL Error
			//CHECK_GL_ERROR();
		}
	}

	bool ShaderProgram::Load()
	{
		if( m_Loaded )
		{
			gLogManager->WriteLog("ShaderProgram already loaded");
			return false;
		}

		File file(m_FileName);

		if(file.Open(File::eFM_Read))
		{
			unsigned long len = file.GetFileLength();

			if ( len == 0 )
			{
				return false;
			}

			char* shaderSource = (char*)malloc(len + 1);

			if ( shaderSource == NULL )
			{
				gLogManager->WriteLog("Memory not available to load shader " + m_FileName );
				return false;
			}

			m_ShaderSource = shaderSource;
			free(shaderSource);
			m_Loaded = true;
		}
		else
		{
			gLogManager->WriteLog("Unable to read shader file : " + m_FileName);
			return false;
		}
		return true;
	}

	bool ShaderProgram::Compile()
	{
		//if (!useGLSL) return false;

		if( !m_Loaded )
		{
			gLogManager->WriteLog("ShaderProgram file " + m_FileName + " is not loaded");
			return false;
		}

		if( !m_Compiled )
		{
			GLint compiled = 0;

			GLint	length = (GLint) m_ShaderSource.Length();
			const char* source = m_ShaderSource.CString();
			glShaderSourceARB(m_GLShaderObject, 1, (const GLcharARB **)&source, &length);
			CHECK_GL_ERROR();

			glCompileShaderARB(m_GLShaderObject); 
			CHECK_GL_ERROR();
			glGetObjectParameterivARB(m_GLShaderObject, GL_COMPILE_STATUS, &compiled);
			CHECK_GL_ERROR();

			if (compiled) 
			{
				m_Compiled = true;
			}

			return m_Compiled;
		}
		else
		{
			return true;
		}
		return m_Compiled;
	}

	GLint ShaderProgram::GetAttribLocation(const String& _attribName)
	{
		return glGetAttribLocationARB(m_GLShaderObject, _attribName.CString());
	}

	String ShaderProgram::GetProgramNameFromFilename(const String& _filename) const
	{
		TCharTokenizerItr itr;

		String programName =  GetLastString(_filename,String("/"));
		
		programName =  GetLastString(programName,"\\");

		TCharSeperator sep2(".");
		TCharTokenizer tokens2(std::string(programName.CString()), sep2);

		programName =  *tokens2.begin();

		return String(programName);
	}

	String ShaderProgram::GetLastString(const String& _string, const String& _seperator) const
	{
		TCharSeperator sep(_seperator.CString());
		TCharTokenizer tokens(std::string(_string.CString()), sep);

		TCharTokenizerItr itr = tokens.begin(); 

		std::string lastString =  *itr;

		while( itr != tokens.end() )
		{
			lastString =  *itr;
		}

		return lastString;
	}
}