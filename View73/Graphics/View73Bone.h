/********************************************************************
	filename: 	View73Bone
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Bone_h__
#define __View73Bone_h__

#include "../Utils/View73String.h"
#include "View73Node.h"
#include <vector>
#include <map>

namespace View73
{
	class Bone;

	typedef boost::shared_ptr<Bone> TSharedBonePtr;
	typedef boost::weak_ptr<Bone> TBoneWeakPtr;

	typedef std::vector<TSharedBonePtr> TBoneSharedPtrArray;
	typedef std::map<String,TSharedBonePtr> TBoneSharedPtrMap;

	class Bone : public Node
	{
	private:

		const unsigned int m_Index;

	public:
	
		Bone(const String& _name, unsigned int _index);
		virtual ~Bone();

		inline unsigned int GetIndex() const		{		return m_Index;				}

	private:

		virtual void UpdateFromParent(){}
		virtual void TransformsUpdated(){}
	};
}

#endif //__View73Bone_h__
