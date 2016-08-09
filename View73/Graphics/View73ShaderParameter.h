/********************************************************************
	filename: 	View73ShaderParameter
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73ShaderParameter_h__
#define __View73ShaderParameter_h__

#include "../Math/View73Matrix44.h"
#include "../boost/smart_ptr.hpp"
#include "../Utils/View73String.h"
#include <list>

namespace View73
{
	class ShaderParameter;

	typedef boost::shared_ptr<ShaderParameter> TSharedShaderParameterPtr;
	typedef std::list<TSharedShaderParameterPtr> TSharedShaderParameterList;

	class ShaderParameter
	{
	public:

		enum ShaderParameterType
		{
			SPT_Float,
			SPT_Float2,
			SPT_Float3,
			SPT_Float4,
			SPT_Float2x2,
			SPT_Float3x3,
			SPT_Float4x4,

		};
	private:

		union ParameterData
		{
			float FloatData[16];
		};

		const ShaderParameterType m_ParameterType;
		ParameterData m_ParameterData;

		const String m_ParamName;
	
	public:
	
		ShaderParameter(const String& _name, ShaderParameterType _parameterType);
		~ShaderParameter();

		void SetValue(float _value);

		inline ShaderParameterType GetParameterType() const		{	m_ParameterType;			}
		inline const String& GetName() const					{	return m_ParamName;			}
	};
}

#endif //__View73ShaderParameter_h__
