#include "Player.h"
#include "GameInputKeys.h"
#include "GameActorTypes.h"
#include "GLKeyInputMethod.h"
#include "GameInputBinding.h"
#include "GameComponents/View73ActorManager.h"
#include "boost/bind.hpp"
#include "Utils/View73ObjMeshLoader.h"
#include "Graphics/View73MeshInstance.h"
#include "Graphics/View73MeshManager.h"
#include "GameComponents/View73ControllerManager.h"

namespace Game
{
	Player* Player::m_Instance = NULL;

	Player::Player()
		: m_Initialized(false)
	{
	}

	Player::~Player()
	{
		m_PlayerToken.reset();
	}

	void Player::Initialize(View73::TSharedSceneManagerPtr _sceneManager,View73::TDynamicsWorldSharedPtr _world,View73::TInputSystemSharedPtr _ipSystem,Keys* _keys)
	{
		if(m_Initialized)
		{
			return;
		}

		m_Initialized = true;

		/*View73::TActorAutoPtr player(new View73::Character((unsigned int)GAT_Player,_world,100.0f,10.3f,View73::Vector3(-0.0f,40.0f,0.0f),View73::Vector3::UNIT_X));
		//View73::TActorAutoPtr player(new View73::Car(GAT_Player,m_DynamicsWorld));

		//_keyIpMethod->AddGameKeyListener(player);

		//View73::TActorSharedPtr playerActor = player;

		View73::TInputBindingAutoPtr inputBinding(new GameInputBinding());

		View73::TInputMethodAutoPtr keyInputMethod(new GLKeyInputMethod(inputBinding,_keys));
		View73::TInputMethodWeakPtr keyIPMethodWeakPtr = inputSystem->AddInputMethod(keyInputMethod);
		
		View73::TActorCrDstCondition crtDestCond = View73::TActorCrDstCondition(&Player::PlayerCharCreatDestRemoveCondition);

		m_PlayerToken = View73::gActorManager->AddActor(player,crtDestCond,crtDestCond,crtDestCond);

		View73::TActorTokenSharedPtr playerToken = m_PlayerToken.lock();
		View73::TActorWeakPtr actorToListener = playerToken->GetActor();

		View73::TInputMethodSharedPtr keyIPMethodSharedPtr = keyIPMethodWeakPtr.lock();
		//keyIPMethodSharedPtr->AddGameKeyListener(actorTokenToListener);

		m_PlayerController.reset(new GamePlayerCharacterController(actorToListener));

		(static_cast<GLKeyInputMethod*>(keyIPMethodSharedPtr.get()))->AddGameKeyListener(m_PlayerController);*/

		View73::ObjMeshLoader loader;

		View73::MeshManager::TMeshCreator creator = boost::bind(&View73::ObjMeshLoader::LoadMesh,&loader,View73::String("../Media/wheel.obj") );
		View73::TSharedMeshPtr wheelMesh = View73::gMeshManager->CreateMesh(creator);

		creator = boost::bind(&View73::ObjMeshLoader::LoadMesh,&loader,View73::String("../Media/car.obj") );
		View73::TSharedMeshPtr chesisMesh = View73::gMeshManager->CreateMesh(creator);



		View73::CarType carType;

		View73::TActorAutoPtr player(new View73::Car((unsigned int)GAT_Car,View73::String("PlayerCar"),_sceneManager,_world,carType));

		View73::Car* car = (View73::Car*)player.get();

		car->SetWheelMesh(wheelMesh->CreateMeshInstance());
		car->SetChesisMesh(chesisMesh->CreateMeshInstance());

		View73::TInputBindingAutoPtr inputBinding(new GameInputBinding());

		View73::TInputMethodAutoPtr keyInputMethod(new GLKeyInputMethod(inputBinding,_keys));
		View73::TInputMethodSharedPtr keyIPMethodSharedPtr = _ipSystem->AddInputMethod(keyInputMethod);
		
		View73::TActorCrDstCondition crtDestCond = View73::TActorCrDstCondition(&Player::PlayerCharCreatDestRemoveCondition);

		m_PlayerToken = View73::gActorManager->AddActor(player,crtDestCond,crtDestCond,crtDestCond);

		m_PlayerCharacter = m_PlayerToken->GetActor();

		

		//keyIPMethodSharedPtr->AddGameKeyListener(actorTokenToListener);

		m_CarController.reset(new GameCarController(m_PlayerCharacter));
		
		View73::gControllerManager->AddController(m_CarController);

		(static_cast<GLKeyInputMethod*>(keyIPMethodSharedPtr.get()))->AddGameKeyListener(m_CarController);

	}

	//-----------------------------------------------------------------------------
	//static functions

	void Player::CreateInstance()
	{
		if(!m_Instance)
		{
			m_Instance = new Player();
		}
	}

	void Player::DestroyInstance()
	{
		if(m_Instance)
		{
			delete m_Instance;
			m_Instance = NULL;
		}
	}

	Player* Player::Get()
	{
		return m_Instance;
	}

	bool Player::PlayerCharCreatDestRemoveCondition()
	{
		return false;
	}

}

