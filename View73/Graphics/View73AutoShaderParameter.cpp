#include "View73AutoShaderParameter.h"

namespace View73
{
	const AutoShaderParameter gAutoShaderParameterNames[ASPT_Count] = 
					{
						//Name						//ParameterType
						{"World",					ShaderParameter::SPT_Float4x4	},			//ASPT_World
						{"WorldView",				ShaderParameter::SPT_Float4x4	},			//ASPT_WorldView
						{"WorldViewProjection",		ShaderParameter::SPT_Float4x4	},			//ASPT_WorldViewProjection
						{"Model",					ShaderParameter::SPT_Float4x4	},			//ASPT_Model
						{"ModelView",				ShaderParameter::SPT_Float4x4	},			//ASPT_ModelView
						{"ModelViewProjection",		ShaderParameter::SPT_Float4x4	},			//ASPT_ModelViewProjection
					};
}