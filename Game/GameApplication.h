/********************************************************************
	filename: 	GameApplication
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __GameApplication_h__
#define __GameApplication_h__

#include "../View73/View73Application.h"
#include "../View73/View73BulletPhysics/View73Physics.h"
#include "../View73/GameComponents/View73ActorOrToken.h"
#include "../View73/Components/View73InputMethodKey.h"
#include "../View73/Graphics/View73GraphicsRoot.h"
#include "../View73/Components/View73InputManager.h"
#include "Player.h"
#include "../View73/Debug/View73DebugScene.h"
#include "../View73/Graphics/View73Skeleton.h"

namespace Game
{
	class BasicCameraController;

	class GameApplication : public View73::Application
	{
	private:

		View73::TDynamicsWorldSharedPtr m_DynamicsWorld;

		View73::TInputSystemSharedPtr m_InputSystem;
		View73::TSharedViewportPtr m_MainViewport;

		View73::TSharedSceneManagerPtr m_MainSceneManager;
		
		bool m_Initialized;

		View73::TSharedFrustrumPtr m_MainCamera;
		BasicCameraController *m_CameraController;

		float* m_WorldCollisionVertices;
		unsigned int *m_WorldCollisionIndices;
		btTriangleIndexVertexArray* m_IndexVertexArrays;

		View73::TSharedSkeletonPtr m_Skeleton;


#ifdef DEBUG_DRAW
		View73::TSharedDebugScenePtr m_DebugScene;
#endif

	public:

		GameApplication(float _width, float _height);
		virtual ~GameApplication();

		virtual void WindowSizeChanged(float _newWidth, float _newHeight);

		//called before update call
		//if returns false application will quit...
		virtual bool PreUpdate();

		//Called before render call
		virtual void Update(const View73::FrameEvent& _event);

		void InitializeGame(Keys* _keys);

		void PlayerEnterTrigger(View73::TActorTokenWeakPtr _player);

	private:

		void CreatePlayer(View73::TInputSystemSharedPtr _keyIpSystem, Keys* _keys);

		void InitializeHUD();

		void LoadLevel();
		View73::TBulletRigidBodySharedPtr LoadLevelCollision();

		void InitializeTestSkeleton();

#ifdef DEBUG_DRAW
		void InitializeDebugScene();
		void DestroyDebugScene();
#endif
	};
}

#endif