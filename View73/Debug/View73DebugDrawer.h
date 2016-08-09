/********************************************************************
	filename: 	View73DebugDrawer
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73DebugDrawer_h__
#define __View73DebugDrawer_h__

#include "../Math/View73Vector3.h"
#include "../Graphics/View73Colour.h"
#include "../Math/View73AxisAlignedBox3.h"
#include "../Utils/View73String.h"
#include "../boost/smart_ptr.hpp"
#include "../Bullet/LinearMath/btIDebugDraw.h"

namespace View73
{
	class DebugDrawer;

	typedef boost::shared_ptr<DebugDrawer> TSharedDebugDrawerPtr;
	typedef boost::weak_ptr<DebugDrawer> TDebugDrawerWeakPtr;
	typedef std::auto_ptr<DebugDrawer> TDebugDrawerAutoPtr;

	class DebugDrawer : public btIDebugDraw
	{
	public:

		DebugDrawer(){}
		virtual ~DebugDrawer(){}

		virtual void DrawLine(const Vector3& _from, const Vector3& _to, const Colour& _fromColor, const Colour& _toColor) = 0;
		virtual void DrawLine(const Vector3& _from, const Vector3& _to, const Colour& _color) = 0;
		virtual void DrawSphere (const Vector3& _p, float _radius, int _slices, int _stacks, const Colour& _color) = 0;
		virtual void DrawBox (const AxisAlignedBox3& _box, const Colour& _color) = 0;
	};
}

#endif