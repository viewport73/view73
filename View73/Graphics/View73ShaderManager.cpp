#include "View73ShaderManager.h"

namespace
{
	using namespace View73;

	static bool glslExtensionsInitialized = false;
	static bool glslAvailable = false;
	static bool glslGPUShader4 = false;

	bool HasGLSLSupport();
	bool InitOpenGLExtensions();
	bool HasGeometryShaderSupport();
	bool HasShaderModel4();

	bool InitOpenGLExtensions()
	{
		if (glslExtensionsInitialized) 
		{
			return true;
		}

		glslExtensionsInitialized = true;

		GLenum err = glewInit();

		String error;

		if (GLEW_OK != err)
		{
			error = error + "Error:";
			error = error + (char*)(glewGetErrorString(err));
			glslExtensionsInitialized = false;
			return false;
		}

		error = error + "OpenGL Vendor: ";
		error = error + (char*)(glGetString(GL_VENDOR));
		error = error + "\n";
		error = error + "OpenGL Renderer: ";
		error = error + (char*)(glGetString(GL_RENDERER));
		error = error + ("\n");
		error = error + "OpenGL Version: ";
		error = error + (char*)(glGetString(GL_VERSION));
		error = error + "\n\n";
		//cout << "OpenGL Extensions:\n" << (char*) glGetString(GL_EXTENSIONS) << "\n\n";
		
		gLogManager->WriteLog(error);
		
		HasGLSLSupport();

		return true;
	}


	bool HasGLSLSupport()
	{
		glslGPUShader4     = HasShaderModel4();

		if (glslAvailable) 
		{
			return true;  // already initialized and GLSL is available
		}

		glslAvailable = true;

		String mssg;

		if (GLEW_VERSION_2_0)
		{
			mssg = mssg + "OpenGL 2.0 (or higher) is available!";
		}
		else if (GLEW_VERSION_1_5)
		{
			mssg = mssg + "OpenGL 1.5 core functions are available";
		}
		else if (GLEW_VERSION_1_4)
		{
			mssg = mssg + "OpenGL 1.4 core functions are available";
		}
		else if (GLEW_VERSION_1_3)
		{
			mssg = mssg + "OpenGL 1.3 core functions are available";
		}
		else if (GLEW_VERSION_1_2)
		{
			mssg = mssg + "OpenGL 1.2 core functions are available";
		}

		if (GL_TRUE != glewGetExtension("GL_ARB_fragment_shader"))
		{
			mssg = mssg + "[WARNING] GL_ARB_fragment_shader extension is not available!\n";
			glslAvailable = false;
		}

		if (GL_TRUE != glewGetExtension("GL_ARB_vertex_shader"))
		{
			mssg = mssg + "[WARNING] GL_ARB_vertex_shader extension is not available!\n";
			glslAvailable = false;
		}

		if (GL_TRUE != glewGetExtension("GL_ARB_shader_objects"))
		{
			mssg = mssg + "[WARNING] GL_ARB_shader_objects extension is not available!\n";
			glslAvailable = false;
		}

		if (glslAvailable)
		{
			mssg = mssg + "[OK] OpenGL Shading Language is available!\n\n";
		}
		else
		{
			mssg = mssg + "[FAILED] OpenGL Shading Language is not available...\n\n";
		}   

		gLogManager->WriteLog(mssg);

		return glslAvailable;
	}

	bool HasGeometryShaderSupport(void)
	{
		if (GL_TRUE != glewGetExtension("GL_EXT_geometry_shader4"))
			return false;

		return true;
	}

	bool HasShaderModel4(void)
	{
		if (GL_TRUE != glewGetExtension("GL_EXT_gpu_shader4"))
			return false;

		return true;
	}
}

namespace View73
{
	ShaderManager* ShaderManager::m_Instance = NULL;
	
	ShaderManager::ShaderManager()
	{
		InitOpenGLExtensions();
		CreateAllAutoShaderParameters();
	}

	ShaderManager::~ShaderManager()
	{
		ClearAllShaderPrograms();
		ClearAllAutoShaderParameters();
	}
	
	void ShaderManager::ClearAllShaderPrograms()
	{
		for( unsigned int i = 0 ; i < ShaderProgram::SPT_Count ; i++ )
		{
			ClearAllShaderProgramsFromList(m_AllShaderPrograms[i]);
		}
	}

	void ShaderManager::ClearAllShaderProgramsFromList(TSharedShaderProgramsList& _programList)
	{
		TSharedShaderProgramsList::iterator itr = _programList.begin();
		TSharedShaderProgramsList::iterator end = _programList.end();

		for( ; itr != end ; itr++ )
		{
			BOOST_ASSERT_MSG((*itr).use_count() == 1, (String("Shader program named ") + (*itr)->GetName()
				+ " is still in use, first clear the reference before clear.." ).CString() );

			(*itr).reset();
		}

		_programList.clear();
	}

	void ShaderManager::ClearAllAutoShaderParameters()
	{
	
		for( int i = 0 ; i < ASPT_Count ; i++ )
		{
			BOOST_ASSERT_MSG(m_AutoShaderParameters[i].use_count() == 1, (String("Shader program named ") + m_AutoShaderParameters[i]->GetName()
				+ " is still in use, first clear the reference before clear.." ).CString() );

			m_AutoShaderParameters[i].reset();
		}
	}

	TSharedVertexProgramPtr ShaderManager::CreateVertexProgram(const String& _fileName)
	{
		TSharedVertexProgramPtr newVertexProgram(new VertexProgram(_fileName));
		
		if(newVertexProgram->Load())
		{
			if(newVertexProgram->Compile())
			{
				m_AllShaderPrograms[ShaderProgram::SPT_Vertex].push_back(newVertexProgram);
				return newVertexProgram;
			}
			else
			{
				gLogManager->WriteLog("Unable to compile shader program");
				newVertexProgram.reset();
			}
		}
		else
		{
			gLogManager->WriteLog("Unable to load shader program");
			newVertexProgram.reset();
		}

		return TSharedVertexProgramPtr();
	}

	TSharedFragmentProgramPtr ShaderManager::CreateFragmentProgram(const String& _fileName)
	{
		TSharedFragmentProgramPtr newFragmentProgram(new FragmentProgram(_fileName));

		if(newFragmentProgram->Load())
		{
			if(newFragmentProgram->Compile())
			{
				m_AllShaderPrograms[ShaderProgram::SPT_Fragment].push_back(newFragmentProgram);
				return newFragmentProgram;
			}
			else
			{
				gLogManager->WriteLog("Unable to compile shader program");
				newFragmentProgram.reset();
			}
		}
		else
		{
			gLogManager->WriteLog("Unable to load shader program");
			newFragmentProgram.reset();
		}

		return TSharedFragmentProgramPtr();
	}

	void ShaderManager::CreateAllAutoShaderParameters()
	{
		for( int i = 0 ; i < ASPT_Count ; i++ )
		{
			m_AutoShaderParameters[i].reset(new ShaderParameter(gAutoShaderParameterNames[i].ParameterName,gAutoShaderParameterNames[i].ParameterType));
		}
	}

	TSharedShaderParameterPtr ShaderManager::GetSharedAutoShaderParameter(AutoShaderParameterType _paramType)
	{
		BOOST_ASSERT_MSG(_paramType >= 0 && _paramType < ASPT_Count, (String("Parameter type always has to be between 0 to ") + ASPT_Count).CString() );
		return m_AutoShaderParameters[_paramType];
	}

	//--------------------------------------------------------------------
	//Static functions
	void ShaderManager::CreateInstance()
	{
		if(m_Instance == NULL)
		{
			m_Instance = new ShaderManager();
		}
	}

	void ShaderManager::DestroyInstance()
	{
		if(m_Instance != NULL)
		{
			delete m_Instance;
			m_Instance = NULL;
		}
	}

	ShaderManager* ShaderManager::Get()
	{
		return m_Instance;
	}

	//--------------------------------------------------------------------
}