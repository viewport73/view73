#include "GameApplication.h"
#include "Graphics/View73BasicSceneManager.h"
#include "Graphics/View73OverlaySceneManager.h"
#include "Graphics/View73MeshManager.h"
#include "Graphics/View73LightManager.h"
#include "Models/Teapot.h"
#include "View73BulletPhysics/View73Physics.h"
#include "Components/View73TransformerManager.h"
#include "Components/View73RigidBodyToNodeTransformer.h"
#include "Debug/View73GLDebugDrawer.h"
#include "Components/View73InputMethodKeyListener.h"
#include "GameActorTypes.h"
#include "GameComponents/View73ActorManager.h"
#include "Components/View73FunctionExecuterCommand.h"
#include "Graphics/View73OverlayFrustrum.h"
#include "boost/bind.hpp"
#include "Utils/View73ObjMeshLoader.h"
#include "Graphics/View73MeshInstance.h"
#include "BasicCameraController.h"
#include "Utils/View73GeometryBinary.h"
#include "Utils/View73SkeletonBinary.h"
#include "Debug/View73PhysicsDebugObject.h"
#include "Debug/View73SkeletonDebugObject.h"

namespace Game
{
	GameApplication::GameApplication(float _width, float _height)
	: m_Initialized(false)
	, m_IndexVertexArrays(NULL)
	, m_WorldCollisionVertices(NULL)
	, m_WorldCollisionIndices(NULL)
	{
		Teapot pot;
		m_MainSceneManager = View73::gGraphicsRoot->CreateSceneManager(View73::BasicSceneManager::GetClassType(),View73::String("Test") );

		m_MainViewport = View73::gGraphicsRoot->CreateViewport(View73::String("dfds"),0,0,(unsigned int)_width ,(unsigned int)_height);
		m_MainCamera = m_MainViewport->CreateCamera(View73::Camera::GetCreationFunction(),View73::String("Test"),View73::Frustrum::ePT_PERSPECTIVE,m_MainSceneManager);
		View73::Camera* cam = static_cast<View73::Camera*>(m_MainCamera.get());
		cam->SetPosition(View73::Vector3(-20,0.0,0));
		cam->SetLookAt(View73::Vector3(-20,-20,0));
		cam->SetUpAxis(View73::Vector3(0,0,-1));
		cam->SetFarClipDistance(1000);

		//test.InitPhysics();

		m_DynamicsWorld = View73::gPhysics->CreateWorld(View73::String("TestWorld"),View73::WT_DiscreteDynamicWorld);

		m_DynamicsWorld->SetGravity(btVector3(0,-9.8f,0));

		LoadLevel();

		m_DynamicsWorld->ClientResetScene();

		InitializeTestSkeleton();

#ifdef DEBUG_DRAW
		InitializeDebugScene();
#endif
	}

	GameApplication::~GameApplication()
	{

#ifdef DEBUG_DRAW
		DestroyDebugScene();
#endif

		m_Skeleton.reset();

		delete m_CameraController;
		m_CameraController = NULL;

		Player::DestroyInstance();

		if(m_WorldCollisionVertices)
		{
			delete [] m_WorldCollisionVertices;
			m_WorldCollisionVertices = NULL;
		}
		if( m_WorldCollisionIndices )
		{
			delete [] m_WorldCollisionIndices;
			m_WorldCollisionIndices = NULL;
		}

		if(m_IndexVertexArrays)
		{
			delete m_IndexVertexArrays;
			m_IndexVertexArrays = NULL;
		}
	}

	void GameApplication::InitializeGame(Keys* _keys)
	{
		if(!m_Initialized)
		{
			View73::TInputSystemAutoPtr inputSystem(new View73::DefaultInputSystem());
			
			m_InputSystem = View73::gInputManager->RegisterInputSystem(inputSystem);

			m_Initialized = true;

			CreatePlayer(m_InputSystem,_keys);

			//InitializeHUD();

			m_CameraController = new BasicCameraController(m_MainCamera);
			m_CameraController->SetFollowActor(gPlayer->GetActor());


			m_DynamicsWorld->ClientResetScene();
		}
	}

	void GameApplication::CreatePlayer(View73::TInputSystemSharedPtr _keyIpSystem, Keys* _keys)
	{
		View73::TriggerDesc desc;

		desc.collisionShape.width = 10.0f;
		desc.collisionShape.height = 10.0f;
		desc.collisionShape.depth = 10.0f;
		desc.transform.setOrigin(btVector3(0,8,0));
		//desc.transform.setRotation(btQuaternion(btVector3(0,0,1.0f),3.1415926535897932384626433832795f/9.0f) );
		
		/*View73::ActorEnterExitTrigger *rawTrigger = new View73::ActorEnterExitTrigger(desc,m_PlayerToken);
		//rawTrigger->
		View73::TCommandAutoPtr weakEnterCommand(new View73::FunctionExecuterCommand(boost::bind(&GameApplication::PlayerEnterTrigger,this,m_PlayerToken)) );

		rawTrigger->AddCommand(weakEnterCommand,View73::ActorEnterExitTrigger::ET_OnEnter);

		View73::TTriggerAutoPtr autoTrigger(rawTrigger);
		m_DynamicsWorld->AddTrigger(autoTrigger);*/

		//Initialize(View73::TDynamicsWorldSharedPtr _world,View73::TInputSystemWeakPtr _ipSystem,Keys* _keys);
		Player::CreateInstance();
		gPlayer->Initialize(m_MainSceneManager,m_DynamicsWorld,_keyIpSystem,_keys);

	}

	void GameApplication::InitializeHUD()
	{
		View73::TSharedSceneManagerPtr scnMgr = View73::gGraphicsRoot->CreateSceneManager(View73::OverlaySceneManager::GetClassType(),View73::String("OverlaySceneManager") );


		View73::TSharedSceneNodePtr node = scnMgr->CreateChildSceneNodeOfNode(scnMgr->GetRootSceneNode(),View73::String("ScreenNode") );

		View73::TOverlayAutoPtr autoOverlay(new View73::OverlayScreen(View73::String("Bckground") ,View73::Rect( 0, 320 , 480, 480 - 100 ) ));
		View73::TOverlaySharedPtr overlay = (static_cast<View73::OverlaySceneManager*>(scnMgr.get()))->AddOverlay(autoOverlay);
		node->AddRenderable(overlay);

		View73::TSharedFrustrumPtr frustrum = m_MainViewport->CreateCamera(View73::OverlayFrustrum::GetCreationFunction(),View73::String("OverlayCamera"),View73::Frustrum::ePT_ORTHOGRAPHIC,scnMgr);
		frustrum->SetCustomProjeParams(0,320,0,480);
		/*View73::Camera* cam = static_cast<View73::Camera*>(frustrum.get());
		cam->SetPosition(View73::Vector3(0,30,200));
		cam->SetLookAt(View73::Vector3(0,30,0));
		cam->SetFarClipDistance(1000);*/
	}

	void GameApplication::WindowSizeChanged(float _newWidth, float _newHeight)
	{
	}

	//called before update call
	//if returns false application will quit...
	bool GameApplication::PreUpdate()
	{
		return true;
	}

	//Called before render call
	void GameApplication::Update(const View73::FrameEvent& _event)
	{	
		m_CameraController->Update(_event);
	}

	void GameApplication::PlayerEnterTrigger(View73::TActorTokenWeakPtr _player)
	{
		int i = 0;
		i++;
	}

	void GameApplication::LoadLevel()
	{
		//add the city
		{
			View73::ObjMeshLoader loader;

			View73::MeshManager::TMeshCreator creator = boost::bind(&View73::ObjMeshLoader::LoadMesh,&loader,View73::String("../Media/city.obj") );
			View73::TSharedSceneNodePtr node = m_MainSceneManager->CreateChildSceneNodeOfNode(m_MainSceneManager->GetRootSceneNode(),View73::String("LevelNode") );
			View73::TSharedSceneNodePtr lightnode = m_MainSceneManager->CreateChildSceneNodeOfNode(m_MainSceneManager->GetRootSceneNode(),View73::String("LevelLightNode") );

			View73::TSharedLightPtr light = View73::gLightManager->CreateLight(View73::String("TestLight") );
			//light->s

			View73::TSharedMeshPtr mesh = View73::gMeshManager->CreateMesh(creator);
			node->AddRenderable(mesh->CreateMeshInstance());
			lightnode->AddLight(light);

			light->SetPosition(View73::Vector3(0.0f,-50.0f,0.0f));


			View73::TBulletRigidBodySharedPtr body = LoadLevelCollision();

			View73::TTransformerAutoPtr trans(new View73::RigidBodyToNodeTransformer(body,node));

			View73::gTransformerManager->AddTransformer(trans);
		}

		//test View73 binary loader
		{
			View73::GeometryBinary geometryBinary("../Media/bin/pCylinderShape1.pgb");

			View73::MeshManager::TMeshCreator creator = boost::bind(&View73::GeometryBinary::CreateMeshWithData,&geometryBinary );
			View73::TSharedSceneNodePtr node = m_MainSceneManager->CreateChildSceneNodeOfNode(m_MainSceneManager->GetRootSceneNode(),View73::String("BinaryDataTest") );

			View73::TSharedMeshPtr mesh = View73::gMeshManager->CreateMesh(creator);
			node->AddRenderable(mesh->CreateMeshInstance());
		}


	}

	View73::TBulletRigidBodySharedPtr GameApplication::LoadLevelCollision()
	{
		int vertStride = 3*sizeof(float);
		int indexStride = 3*sizeof(int);

		unsigned int vertexBufferCount,indexBufferCount;

		View73::ObjMeshLoader loader;

		loader.LoadMesh(View73::String("../Media/city.obj"),m_WorldCollisionVertices,vertexBufferCount,m_WorldCollisionIndices,indexBufferCount);

		unsigned int triangleCount = indexBufferCount/3;
		unsigned int verticesCount = vertexBufferCount/3;


		m_IndexVertexArrays = new btTriangleIndexVertexArray(triangleCount,
									(int*)m_WorldCollisionIndices,indexStride,verticesCount,m_WorldCollisionVertices,vertStride);

		bool useQuantizedAabbCompression = true;

		btVector3 aabbMin(-1000,-1000,-1000),aabbMax(1000,1000,1000);

		btBvhTriangleMeshShape *trimeshShape  = new btBvhTriangleMeshShape(m_IndexVertexArrays,useQuantizedAabbCompression,aabbMin,aabbMax);
	
/*		int maxSerializeBufferSize = 1024*1024*5;
		btDefaultSerializer*	serializer = new btDefaultSerializer(maxSerializeBufferSize);
		serializer->startSerialization();
#ifdef SERIALIZE_SHAPE
		trimeshShape->serializeSingleShape(serializer);
#else
		trimeshShape->serializeSingleBvh(serializer);
#endif

		serializer->finishSerialization();
		FILE* f2 = fopen("../Media/myShape.bullet","wb");
		fwrite(serializer->getBufferPointer(),serializer->getCurrentBufferSize(),1,f2);
		fclose(f2);*/

		View73::RigidBodyDesc desc;
		desc.mass = 0.0f;//static;
		desc.collisionShape.type = View73::CS_None;
		desc.collisionShape.shape = trimeshShape;
		desc.transform.setOrigin(btVector3(0,-0,0));

		View73::TBulletRigidBodySharedPtr body = m_DynamicsWorld->CreateCollisionBody(desc);


		body.get()->setCollisionFlags(body.get()->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);//STATIC_OBJECT);

		//enable custom material callback
		//staticBody->setCollisionFlags(staticBody->getCollisionFlags()  | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

		return body;
	}

	void GameApplication::InitializeTestSkeleton()
	{
		View73::SkeletonBinary sklBinary("../Media/bin/Skeleton/GrummanGoose_Rig.psb");
		bool loaded = sklBinary.LoadFromFile();

		if(loaded)
		{
			m_Skeleton = sklBinary.CreateSkeletonWithData();
		}
	}

#ifdef DEBUG_DRAW
	void GameApplication::InitializeDebugScene()
	{
		m_DebugScene.reset(new View73::DebugScene(View73::TDebugDrawerAutoPtr(new View73::GLDebugDrawer()),m_MainCamera) );
		m_MainCamera->AddOnRenderListener(m_DebugScene);
		m_DebugScene->AddDebugObject(View73::TDebugObjectAutoPtr(new View73::PhysicsDebugObject(m_DynamicsWorld)));
	
		m_DebugScene->AddDebugObject(View73::TDebugObjectAutoPtr(new View73::SkeletonDebugObject(m_Skeleton->CreateSkeletonInstance())));
	}

	void GameApplication::DestroyDebugScene()
	{
		BOOST_ASSERT_MSG(m_DebugScene.use_count() == 1, "Debug scene is already being used by another object, please clear all references before deleting" );
		m_DebugScene.reset();
	}
#endif
}