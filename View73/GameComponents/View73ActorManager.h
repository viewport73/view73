/********************************************************************
	filename: 	View73ActorManager
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73ActorManager_h__
#define __View73ActorManager_h__

#include "View73ActorOrToken.h"
#include <list>

namespace View73
{
	class ActorManager
	{
	public:

		typedef std::list<TActorTokenSharedPtr> TActorTokenSharedPtrList;

	private:

		static ActorManager *m_Instance;

		TActorTokenSharedPtrList m_AllActors;

	public:

		//--------------------------------------------------------------------
		//Static functions
		static void CreateInstance();
		static void DestroyInstance();
		static ActorManager* Get();
		//--------------------------------------------------------------------

		ActorManager();
		~ActorManager();

		void ClearAllActors();

		TActorTokenSharedPtr RegisterActor(TActorToken _initialCreator ,TActorCrDstCondition _creatCondition 
			,TActorCrDstCondition _destroyCondition, TActorCrDstCondition _removeCond);

		TActorTokenSharedPtr AddActor(TActorAutoPtr _actor,TActorCrDstCondition _creatCondition 
			,TActorCrDstCondition _destroyCondition, TActorCrDstCondition _removeCond);

		void Update(const FrameEvent& _frameEvent);

	};

#define gActorManager ActorManager::Get()
}

#endif