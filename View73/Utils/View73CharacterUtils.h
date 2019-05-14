/********************************************************************
	filename: 	View73CharacterUtils
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Utils_h__
#define __View73Utils_h__

#include "../boost/boost/foreach.hpp"
#include "../boost/boost/tokenizer.hpp"

namespace View73
{
	typedef boost::char_separator<char> TCharSeperator;
	typedef boost::tokenizer<TCharSeperator> TCharTokenizer;
	typedef TCharTokenizer::iterator TCharTokenizerItr;
}

#endif