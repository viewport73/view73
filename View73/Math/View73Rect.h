/********************************************************************
	filename: 	View73Rect
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Rect_h__
#define __View73Rect_h__

namespace View73
{
	class Rect
	{
	public:

		float m_Left;
		float m_Right;
		float m_Top;
		float m_Bottom;

		Rect(float _left,float _right, float _top, float _bottom)
		{
			Set(_left,_right,_top,_bottom);
		}

		inline void Set(float _left,float _right, float _top, float _bottom)
		{
			m_Left = _left;
			m_Right = _right;
			m_Top = _top;
			m_Bottom = _bottom;
		}
	};
}

#endif