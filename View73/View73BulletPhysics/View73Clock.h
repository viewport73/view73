/********************************************************************
	filename: 	View73Clock
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Clock_h__
#define __View73Clock_h__

#include "LinearMath/btQuickprof.h"

namespace View73
{
	class Clock
	{
	private:

		btClock m_BulletClock;

	public:

		Clock(){}
		~Clock(){}

		/// Resets the initial reference time.
		inline void Reset()		{	m_BulletClock.reset();	}

		/// Returns the time in ms since the last call to reset or since 
		/// the btClock was created.
		inline unsigned long int GetTimeMilliseconds()	{	return m_BulletClock.getTimeMilliseconds();	}

		/// Returns the time in us since the last call to reset or since 
		/// the Clock was created.
		inline unsigned long int GetTimeMicroseconds()	{	return m_BulletClock.getTimeMicroseconds();	}
	};
}

#endif