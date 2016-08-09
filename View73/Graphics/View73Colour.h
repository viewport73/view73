/********************************************************************
	filename: 	View73Colour
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Colour_h__
#define __View73Colour_h__

namespace View73
{
	class Colour
	{
	public:
		union
		{
			struct
			{
				float r;
				float g;
				float b;
				float a;
			};

			float colourArray[4];
		};

	public:

		inline Colour()
		{
		}

		inline Colour( float _r, float _g, float _b, float _a)
			: r(_r)
			, g(_g)
			, b(_b)
			, a(_a)
		{
		}
	};
}

#endif