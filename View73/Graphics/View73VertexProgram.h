/********************************************************************
	filename: 	View73VertexProgram
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73VertexShader_h__
#define __View73VertexShader_h__

#include "View73ShaderProgram.h"

namespace View73
{
	class VertexProgram;

	typedef boost::shared_ptr<VertexProgram> TSharedVertexProgramPtr;

	class VertexProgram : public ShaderProgram
	{
	protected:

		friend class ShaderManager;

		VertexProgram(const String& _filename);

	public:

		virtual ~VertexProgram(); 
	};
}

#endif