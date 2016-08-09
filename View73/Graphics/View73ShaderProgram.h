/********************************************************************
	filename: 	View73ShaderProgram
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Shader_h__
#define __View73Shader_h__

#include "../Utils/View73String.h"
#include "View73GlInclude.h"
#include "View73GLError.h"
#include <list>

#include "../boost/smart_ptr.hpp"

namespace View73
{
	class ShaderProgram;

	typedef boost::shared_ptr<ShaderProgram> TSharedShaderProgramPtr;
	typedef std::list<TSharedShaderProgramPtr> TSharedShaderProgramsList;

	class ShaderProgram
	{
	public:

		friend class ShaderPass;
		friend class ShaderManager;

		enum ShaderProgramType
		{
			SPT_Vertex = 0,
			SPT_Fragment,

			SPT_Count
		};

	protected:

		const String m_FileName;
		const String m_ProgramName;
		ShaderProgramType m_ShaderType;
		String m_ShaderSource;
		GLuint m_GLShaderObject;
		bool m_Loaded;
		bool m_Compiled;

		ShaderProgram(ShaderProgramType _shaderType,const String& _filename);

		String GetProgramNameFromFilename(const String& _filename) const;
		String GetLastString(const String& _string, const String& _seperator) const;

		void Destroy();
		
		GLint GetAttribLocation(const String& _attribName);
		inline ShaderProgramType GetShaderType() const					{	return m_ShaderType;		}
		
		inline GLuint GetShaderObject() const							{	return m_GLShaderObject;	}

		bool Load();
		bool Compile();

	public:

		virtual ~ShaderProgram();

		inline const String& GetName() const					{	return m_ProgramName;		}
	};

}

#endif