/********************************************************************
	filename: 	View73ShaderEffect
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73ShaderEffect_h__
#define __View73ShaderEffect_h__

#include "View73ShaderPass.h"
#include "View73ShaderEffectInstance.h"

#define MAX_PASS_COUNT 3

namespace View73
{
	class ShaderEffect;

	typedef boost::shared_ptr<ShaderEffect> TSharedShaderEffectPtr;

	class ShaderEffect
	{
	private:

		class ShaderEffectInstanceImpl;
		friend class ShaderEffectInstanceImpl;

		TSharedShaderPassArray m_AllPasses;

		TSharedShaderEffectInstanceArray m_AllEffectInstances;

		TSharedShaderPassPtr m_ActivePass;

		void ClearAllPasses();
		void ClearAllShaderEffectInstances();

		void BeginPass(unsigned short _passIndex);
		void EndPass();

	public:

		ShaderEffect();
		~ShaderEffect();

		//void AddShaderPass( TSharedVertexProgramPtr _vertexProgram,TSharedFragmentProgramPtr _fragmentProgram);

		TSharedShaderEffectInstancePtr CreateShaderEffectInstance();

		inline unsigned short GetPassCount() const	{	return (unsigned short)(m_AllPasses.size());		}
	};
}

#endif //__View73ShaderEffect_h__
