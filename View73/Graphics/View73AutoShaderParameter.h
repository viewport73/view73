/********************************************************************
	filename: 	View73AutoShaderParameter
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73AutoShaderParameter_h__
#define __View73AutoShaderParameter_h__

#include "../Utils/View73String.h"
#include "View73ShaderParameter.h"

namespace View73
{
	enum AutoShaderParameterType
	{
		ASPT_World,
		ASPT_WorldView,
		ASPT_WorldViewProjection,
		ASPT_Model,
		ASPT_ModelView,
		ASPT_ModelViewProjection,

		ASPT_Count
	};

	struct AutoShaderParameter
	{
		String ParameterName;
		ShaderParameter::ShaderParameterType ParameterType;
	};

	extern const AutoShaderParameter gAutoShaderParameterNames[ASPT_Count];
}

#endif //__View73AutoShaderParameter_h__
