/********************************************************************
	filename: 	View73Transformer
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Transformer_h__
#define __View73Transformer_h__

#include "../boost/smart_ptr.hpp"
#include "../Graphics/View73FrameEvent.h"

namespace View73
{
	class Transformer;
	typedef boost::shared_ptr<Transformer> TTransformerSharedPtr;
	typedef std::auto_ptr<Transformer> TTransformerAutoPtr;

	class Transformer
	{
	private:

	public:

		Transformer()
		{
		}

		virtual ~Transformer()
		{
		}

		virtual void Update(const FrameEvent& _frameEvent) = 0;
	};
}

#endif