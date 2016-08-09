/********************************************************************
	filename: 	View73FragmentProgram
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73FragmentProgram_h__
#define __View73FragmentProgram_h__

#include "View73ShaderProgram.h"

namespace View73
{
	class FragmentProgram;

	typedef boost::shared_ptr<FragmentProgram> TSharedFragmentProgramPtr;

	class FragmentProgram : public ShaderProgram
	{
	protected:

		friend class ShaderManager;

		FragmentProgram(const String& _filename);

	public:

		virtual ~FragmentProgram();

	};
}

#endif