/********************************************************************
	filename: 	View73AxisAlignedBox3
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73AxisAlignedBox3_h__
#define __View73AxisAlignedBox3_h__

#include "View73Vector3.h"

namespace View73 
{
	class AxisAlignedBox3
	{
	private:

		Vector3 m_Min;
		Vector3 m_Max;

	public:

		inline AxisAlignedBox3(){}

		inline AxisAlignedBox3(const Vector3& _min, const Vector3& _max)
			: m_Min(_min)
			, m_Max(_max)
		{
		}

		inline ~AxisAlignedBox3(){}

		inline const Vector3& GetMin() const		{	return m_Min;				}
		inline const Vector3& GetMax() const		{	return m_Max;				}

	};
}

#endif