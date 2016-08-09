/********************************************************************
	filename: 	Player
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __Player_h__
#define __Player_h__

#include "../View73/GameComponents/View73Character.h"
#include "../View73/View73BulletPhysics/View73Physics.h"
#include "../View73/Components/View73DefaultInputSystem.h"
#include "GamePlayerCharacterController.h"
#include "../NeHeGL.h"
#include "GameCarController.h"
#include "../View73/Graphics/View73SceneManager.h"


namespace Game
{
	class Player
	{
	private:

		bool m_Initialized;

		View73::TActorTokenSharedPtr m_PlayerToken;
		View73::TActorWeakPtr m_PlayerCharacter;
		TGamePlayerCharacterControllerSharedPtr m_PlayerController;
		TGameCarControllerSharedPtr m_CarController;

		Player();
		~Player();
                         
		static Player* m_Instance;

	public:

		View73::TActorTokenSharedPtr GetPlayerToken()		{	return m_PlayerToken;		}
		View73::TActorWeakPtr GetActor()	{	return m_PlayerCharacter;	}

	public:
	
		static void CreateInstance();
		static void DestroyInstance();
		static Player* Get();

		static bool PlayerCharCreatDestRemoveCondition();
		
		void Initialize(View73::TSharedSceneManagerPtr _sceneManager,View73::TDynamicsWorldSharedPtr _world,View73::TInputSystemSharedPtr _ipSystem,Keys* _keys);

	private:
	};

#define gPlayer Player::Get()
}
#endif