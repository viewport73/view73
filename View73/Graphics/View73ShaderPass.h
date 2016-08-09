/********************************************************************
	filename: 	View73ShaderPass
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73ShaderPass_h__
#define __View73ShaderPass_h__

#include "View73VertexProgram.h"
#include "View73FragmentProgram.h"

namespace View73
{
	class ShaderPass;

	typedef boost::shared_ptr<ShaderPass> TSharedShaderPassPtr;

	typedef std::vector<TSharedShaderPassPtr> TSharedShaderPassArray;
	
	class ShaderPass
	{
	protected:

		friend class ShaderEffect;

		GLuint						m_ProgramObject;                      // GLProgramObject
		bool						m_Linked;
		
		TSharedVertexProgramPtr		m_VertexProgram;
		TSharedFragmentProgramPtr	m_FragmentProgram;

		ShaderPass(TSharedVertexProgramPtr _vertexProgram, TSharedFragmentProgramPtr _fragmentProgram);

		void Create();
		void Destroy();
		void DetachAllShaders();
		void AttachAllShaders();

		void BindAttribLocation(GLint index, GLchar* name);

		bool Link();

		void BeginPass();
		void EndPass();

	public:

		~ShaderPass();
	};
}

#endif