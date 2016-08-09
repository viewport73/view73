/********************************************************************
	filename: 	View73GLError
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73GLError_h__
#define __View73GLError_h__

#include "../Utils/View73LogManager.h"

namespace View73
{
	// GL ERROR CHECK
	static int CheckGLError(char *file, int line)
	{
		GLenum glErr;
		int    retCode = 0;

		glErr = glGetError();
		while (glErr != GL_NO_ERROR) 
		{
			const GLubyte* sError = gluErrorString(glErr);

			if (sError)
			{
				//cout << "GL Error #" << glErr << "(" << gluErrorString(glErr) << ") " << " in File " << file << " at line: " << line << endl;
				View73::gLogManager->WriteLog("GL Error #" + (unsigned int)glErr + String("(") 
					+ (const char*)gluErrorString(glErr) + ") " + " in File " + file + " at line: " 
					+ line );
			}
			else
			{
				//cout << "GL Error #" << glErr << " (no message available)" << " in File " << file << " at line: " << line << endl;
				View73::gLogManager->WriteLog("GL Error #" + (unsigned int)glErr + String(" (no message available)") + " in File " + file + " at line: " + line );
			}

			retCode = 1;
			glErr = glGetError();
		}
		return retCode;
	}

#define CHECK_GL_ERROR() CheckGLError(__FILE__, __LINE__)
}

#endif