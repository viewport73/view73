/********************************************************************
	filename: 	View73Physics
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Physics_h__
#define __View73Physics_h__

#include "View73BulletTypes.h"
#include "View73DynamicsWorld.h"
#include <list>

namespace View73
{
	class Physics
	{
	public:
		
		typedef std::list<TDynamicsWorldSharedPtr> TDynamicsWorldsList;

	private:

		static Physics *m_Instance;


		TDynamicsWorldsList m_AllWorlds;

		Physics();
		~Physics();

		void ClearAllWorld();
		

	public:

		//--------------------------------------------------------------------
		//Static functions
		static void CreateInstance();
		static Physics* Get();
		static void DestroyInstance();
		//--------------------------------------------------------------------

		TDynamicsWorldSharedPtr CreateWorld(const String& _name , WorldType _worldType);
		TDynamicsWorldSharedPtr GetWorld(const String& _name);
		void DestroyWorld(const String& _name);

		void StepSimulation(float _time);
	};

#define gPhysics Physics::Get()
}

#endif