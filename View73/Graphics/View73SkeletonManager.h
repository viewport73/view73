/********************************************************************
	filename: 	View73SkeletonManager
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73SkeletonManager_h__
#define __View73SkeletonManager_h__

#include <list>
#include "View73Skeleton.h"
#include <boost/smart_ptr.hpp>

namespace View73
{
	class SkeletonManager
	{
	private:
		friend class GraphicsRoot;

		class Impl;
		boost::scoped_ptr<Impl> m_Impl;

		static SkeletonManager *m_Instance;

	private:

		//--------------------------------------------------------------------
		//Static functions
		static void CreateInstance();
		static void DestroyInstance();
		//--------------------------------------------------------------------

		SkeletonManager();
		~SkeletonManager();

	public:

		//--------------------------------------------------------------------
		//Static functions
		static SkeletonManager* Get();
		//--------------------------------------------------------------------

		TSharedSkeletonPtr CreateSkeleton(const String& _skeletonName);
		TSharedSkeletonPtr GetSkeleton(const String& _skeletonName);
		void DestroySkeleton(const String& _skeletonName);

	};

	#define gSkeletonManager SkeletonManager::Get()
}

#endif //__View73SkeletonManager_h__
