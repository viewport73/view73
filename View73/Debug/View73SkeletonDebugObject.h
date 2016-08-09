/********************************************************************
	filename: 	View73SkeletonDebugObject
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73SkeletonDebugObject_h__
#define __View73SkeletonDebugObject_h__

#include "../Graphics/View73SkeletonInstance.h"
#include "View73DebugObject.h"

namespace View73
{
	class SkeletonDebugObject : public DebugObject
	{
	private:

		TSkeletonInstanceWeakPtr m_SkeletonInstance;
	
	public:
	
		SkeletonDebugObject(TSkeletonInstanceWeakPtr _skeleton);
		~SkeletonDebugObject();

		virtual void Render();

	private:

		virtual void DebugDrawerUpdated(){};
		bool CanDelete() const;

		void DrawSkeleton(TSharedSkeletonInstancePtr _skelInst, TSharedDebugDrawerPtr _debugDrawer, TSharedFrustrumPtr _frustrum, TSharedBonePtr _root);
		void DrawBone( TSharedDebugDrawerPtr _debugDrawer, TSharedFrustrumPtr _frustrum, const Matrix44& _boneTransform );
		void DrawBoneLink( TSharedDebugDrawerPtr _debugDrawer, TSharedFrustrumPtr _frustrum, const Matrix44& _parentTransform, const Matrix44& _childTransform );
		float GetRadius(TSharedFrustrumPtr _frustrum, const Matrix44& _boneTransform, float _nearPlaneSize );
	};
}

#endif //__View73SkeletonDebugObject_h__
