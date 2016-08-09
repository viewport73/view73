/********************************************************************
	filename: 	View73Skeleton
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Skeleton_h__
#define __View73Skeleton_h__

#include "../Math/View73Matrix44.h"
#include "../Utils/View73LogManager.h"
#include "View73SkeletonInstance.h"
#include <vector>
#include <map>

namespace View73
{
	class Skeleton;
	
	typedef boost::shared_ptr<Skeleton> TSharedSkeletonPtr;
	typedef boost::weak_ptr<Skeleton> TSkeletonWeakPtr;

	typedef std::list<TSharedSkeletonPtr> TSharedSkeletonPtrList;
	typedef std::map<const String,TSharedSkeletonPtr> TSharedSkeletonMap;

	class Skeleton
	{
	public:

		struct BoneInfo
		{
			String m_Name;
			unsigned int m_BoneIndex;
			Matrix44 m_BoneMatrix;
		};

	private:

		class Impl;
		boost::scoped_ptr<Impl> m_Impl;

	public:
	
		Skeleton(const String& _name);
		virtual ~Skeleton();

		// returns the index of the bone
		// returns -1 if an error occured
		int CreateBoneInfo(const String& _boneName, const Vector3& _bonePos, const Quaternion& _boneRotation = Quaternion::IDENTITY);
		int CreateBoneInfo(const String& _boneName, const Matrix44& _boneMatrix);
		void AddChildToBone(unsigned int _boneIndex, unsigned int _childIndex);

		TSharedSkeletonInstancePtr CreateSkeletonInstance() const;

		const String& GetName() const;

	protected:

		const BoneInfo* GetBoneInfoByName(const String& _boneName) const;
	};
}

#endif //__View73Skeleton_h__
