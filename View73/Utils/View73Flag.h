/********************************************************************
	filename: 	View73Flag
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Flag_h__
#define __View73Flag_h__

namespace View73
{
	template <typename T> class Flag
	{
	private:

		T m_Flags;
	
	public:

		inline Flag() : m_Flags(0){}
		inline Flag(T _flag) : m_Flags(_flag){}
		inline Flag(const Flag& _flag) : m_Flags(_flag.m_Flags){}
		inline ~Flag(){}

		inline void SetFlag( T _flag )				{			m_Flags = m_Flags | _flag;					}
		inline void ClearFlag( T _flag )			{			m_Flags = m_Flags & ~_flag;					}
		inline bool CheckFlag( T _flag )	const	{			return ((m_Flags & _flag) == _flag);		}
		inline void ResetFlag()						{			m_Flags = 0;								}
	};

	typedef Flag<unsigned int> TFlag32;
}

#endif //__View73Flag_h__
