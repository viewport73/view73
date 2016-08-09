/********************************************************************
	filename: 	View73ShaderManager
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73ShaderManager_h__
#define __View73ShaderManager_h__

#include "View73ShaderEffect.h"
#include "View73AutoShaderParameter.h"

namespace View73
{
	class ShaderManager
	{
	private:

		friend class ApplicationRoot;

		TSharedShaderProgramsList m_AllShaderPrograms[ShaderProgram::SPT_Count];
		TSharedShaderParameterPtr m_AutoShaderParameters[ASPT_Count];
	
		//--------------------------------------------------------------------
		//Static functions
		static void CreateInstance();
		static void DestroyInstance();
		//--------------------------------------------------------------------

		ShaderManager();
		~ShaderManager();

		static ShaderManager *m_Instance;

		void CreateAllAutoShaderParameters();

		void ClearAllShaderPrograms();
		void ClearAllShaderProgramsFromList(TSharedShaderProgramsList& _programList);
		void ClearAllAutoShaderParameters();

	public:

		//--------------------------------------------------------------------
		//Static functions
		static ShaderManager* Get();
		//--------------------------------------------------------------------
		
		TSharedVertexProgramPtr CreateVertexProgram(const String& _fileName);
		TSharedFragmentProgramPtr CreateFragmentProgram(const String& _fileName);

		TSharedShaderParameterPtr GetSharedAutoShaderParameter(AutoShaderParameterType _paramType);
		
	};

#define gShaderManager (ShaderManager::Get())
}

#endif