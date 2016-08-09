#include "View73ShaderParameter.h"

namespace View73
{
	ShaderParameter::ShaderParameter(const String& _name, ShaderParameterType _parameterType)
		: m_ParamName(_name)
		, m_ParameterType(_parameterType)
	{

	}

	ShaderParameter::~ShaderParameter()
	{

	}

	void ShaderParameter::SetValue(float _value)
	{
		m_ParameterData.FloatData[0] = _value;
	}
}