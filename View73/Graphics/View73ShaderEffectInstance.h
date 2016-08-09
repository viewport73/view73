/********************************************************************
	filename: 	View73ShaderEffectInstance
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73ShaderEffectInstance_h__
#define __View73ShaderEffectInstance_h__

#include <list>
#include <vector>
#include "../boost/smart_ptr.hpp"
#include "View73ShaderParameter.h"

namespace View73
{
	class ShaderEffectInstance;

	typedef boost::shared_ptr<ShaderEffectInstance> TSharedShaderEffectInstancePtr;
	typedef std::list<TSharedShaderEffectInstancePtr> TSharedShaderEffectInstanceList;
	typedef std::vector<TSharedShaderEffectInstancePtr> TSharedShaderEffectInstanceArray;

	class ShaderEffectInstance
	{
	private:

		friend class Material;

		TSharedShaderParameterList m_ParameterList;

	protected:
	
		ShaderEffectInstance();
		virtual ~ShaderEffectInstance();

		virtual void BeginPass(unsigned short _passIndex) = 0;
		virtual void EndPass() = 0;

	public:

		inline void AddParameter(TSharedShaderParameterPtr _parameter)
		{
			m_ParameterList.push_back(_parameter);
		}

		virtual unsigned short GetPassCount() const = 0;
	};
}

#endif //__View73ShaderEffectInstance_h__
