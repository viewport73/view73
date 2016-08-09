/********************************************************************
	filename: 	View73SkeletonInstance
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73SkeletonInstance_h__
#define __View73SkeletonInstance_h__

#include "../boost/smart_ptr.hpp"
#include <list>
#include "View73Bone.h"

namespace View73
{
	class SkeletonInstance;
	
	typedef boost::shared_ptr<SkeletonInstance> TSharedSkeletonInstancePtr;
	typedef boost::weak_ptr<SkeletonInstance> TSkeletonInstanceWeakPtr;

	class SkeletonInstance
	{
	protected:

		SkeletonInstance(){}
		virtual ~SkeletonInstance(){}

	public:

		virtual void Update() = 0;
		virtual TBoneWeakPtr GetRootBone() const = 0;
		virtual TBoneWeakPtr GetBoneByIndex(unsigned int _index) = 0;
		virtual int GetChildCountOfBone(unsigned int _boneIndex) const = 0;
		virtual int GetBoneIdOfChildOfBone(unsigned int _boneIndex, unsigned int _childIndex) const = 0;
	};
}

#endif