/********************************************************************
	filename: 	View73BulletView73Conversion
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73BulletView73Conversion_h__
#define __View73BulletView73Conversion_h__

#include "../Bullet/LinearMath/btVector3.h"
#include "../Math/View73Vector3.h"
#include "../Graphics/View73Colour.h"

namespace View73
{
	static inline btVector3 ConvertVector3( const Vector3& _vector )
	{
		return btVector3(_vector.x,_vector.y,_vector.z);
	}

	static inline Vector3 ConvertVector3( const btVector3& _vector )
	{
		return Vector3(_vector.getX(),_vector.getY(),_vector.getZ());
	}

	static inline Colour ConvertColor( const btVector3& _vecColor )
	{
		return Colour((float)_vecColor.getX(),(float)_vecColor.getY(),(float)_vecColor.getZ(),1.0f);
	}

	static inline Colour ConvertColor( const btVector3& _vecColor, float _alpha )
	{
		return Colour((float)_vecColor.getX(),(float)_vecColor.getY(),(float)_vecColor.getZ(),_alpha);
	}
}

#endif