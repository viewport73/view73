#include "BasicCameraController.h"


namespace Game
{

	BasicCameraController::BasicCameraController(View73::TSharedFrustrumPtr _camera)
		: m_SharedCameraPtr(_camera)
		, m_PositionOffset(View73::Vector3(0.0f,10.0f,-10.0f))
		, m_LookAtDist(15.0f)
	{
		View73::Camera *camera = dynamic_cast<View73::Camera*>(_camera.get());
		assert(camera);
	}

	BasicCameraController::~BasicCameraController()
	{
		m_SharedCameraPtr.reset();
		m_ActorToFollow.reset();
	}

	void BasicCameraController::SetFollowActor(View73::TActorWeakPtr _actor)
	{	
		View73::Camera *camera = dynamic_cast<View73::Camera*>(m_SharedCameraPtr.get());

		m_ActorToFollow = _actor;	

		View73::TActorSharedPtr strongActor = _actor.lock();

		const View73::Vector3& actorPos = strongActor->GetPosition();
		const View73::Quaternion& rotation = strongActor->GetRotation();

		m_CurrPosition = actorPos + rotation * m_PositionOffset;
		m_CurrLookAt = actorPos + rotation * View73::Vector3::UNIT_Z * m_LookAtDist;

		camera->SetPosition(m_CurrPosition);
		camera->SetLookAt(m_CurrLookAt);
		camera->SetUpAxis(View73::Vector3::UNIT_Y);
	}

	void BasicCameraController::Update(const View73::FrameEvent& _frameEvent)
	{
		View73::Camera *camera = dynamic_cast<View73::Camera*>(m_SharedCameraPtr.get());

		View73::TActorSharedPtr strongActor = m_ActorToFollow.lock();

		const View73::Vector3& actorPos = strongActor->GetPosition();
		const View73::Quaternion& rotation = strongActor->GetRotation();
		View73::Vector3 targetPos = actorPos + rotation * m_PositionOffset;
		View73::Vector3 targetLookAt = actorPos + rotation * View73::Vector3::UNIT_Z * m_LookAtDist;

		m_CurrPosition = m_CurrPosition + ( targetPos - m_CurrPosition ) * 0.25f;
		m_CurrLookAt = m_CurrLookAt + ( targetLookAt - m_CurrLookAt ) * 0.1f;

		camera->SetPosition(m_CurrPosition);
		camera->SetLookAt(m_CurrLookAt);
		camera->SetUpAxis(View73::Vector3::UNIT_Y);
	}
}
