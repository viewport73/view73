/********************************************************************
	filename: 	View73StringTokenizer
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73StringTokenizer_h__
#define __View73StringTokenizer_h__

#include <boost/smart_ptr.hpp>
#include "View73String.h"

namespace View73
{
	class StringTokenizer
	{
	private:

		class Impl;
		class ImplCharSeparator;
		boost::scoped_ptr<Impl> m_Impl;

	public:
	
		StringTokenizer(const String& _string, char _seperator);
		~StringTokenizer();

		void ResetCursor();

		String GetBegin();
		String GetNextToken();
		bool HasNextToken() const;
	};
}

#endif //__View73StringTokenizer_h__
