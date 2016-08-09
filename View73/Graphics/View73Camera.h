/********************************************************************
	filename: 	View73Camera
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Camera_h__
#define __View73Camera_h__

#include "View73Frustrum.h"
#include "../Math/View73Matrix44.h"
#include "../Math/View73Vector3.h"

namespace View73
{
	class Camera;

	typedef boost::shared_ptr<Camera> TSharedCameraPtr;

	class Camera : public Frustrum
	{
	private:

		Vector3 m_Position;
		Vector3 m_Direction;
		Vector3 m_LookAt;
		Vector3 m_UpAxis;
		
		bool m_DirtyViewMatrix;
		Matrix44 m_ViewMatrix;
		Matrix44 m_InvViewMatrix;

	public:

		Camera(const String& _name, ProjectionType _projType,TSharedSceneManagerPtr _sceneManager);
		virtual ~Camera();

		const Vector3& GetPosition()			{	return m_Position;			}
		const Vector3& GetLookAt()				{	return m_LookAt;			}
		const Vector3& GetUpAxis()				{	return m_UpAxis;			}
		const Vector3& GetDirection()			{	return m_Direction;			}
		
		void SetPosition(const Vector3& _pos)	
		{	
			if( m_Position != _pos)
			{
				m_DirtyViewMatrix = true;
				m_Position = _pos;
				ComputeDirection();
			}
		}
		
		void SetLookAt(const Vector3& _lookAt)	
		{	
			if(m_LookAt != _lookAt)
			{
				m_DirtyViewMatrix = true;
				m_LookAt = _lookAt;
				ComputeDirection();
			}
		}
		
		void SetDirection(const Vector3& _dir)
		{
			if(m_Direction != _dir )
			{
				m_DirtyViewMatrix = true;
				m_Direction = _dir;
				ComputeLookAtFromDirection();
			}
		}
		
		inline void SetUpAxis(const Vector3& _upAxis)
		{
			m_UpAxis = _upAxis;
		}

		virtual const Matrix44& GetViewMatrix()
		{
			UpdateViewMatrix();
			return m_ViewMatrix;
		}

		virtual const Matrix44& GetInverseViewMatrix()	
		{	
			UpdateViewMatrix();	
			return m_InvViewMatrix;
		}
	
	private:
		
		void SetViewMatrix();
		
		inline void ComputeDirection()
		{
			Vector3 direction = m_LookAt - m_Position;
			direction.Normalize();
			m_Direction = direction;
		}
		
		inline void ComputeLookAtFromDirection()
		{
			m_LookAt = m_Position + m_Direction;
		}
		
		void UpdateViewMatrix();

		virtual void OnRenderStart();
		virtual void OnRenderEnd();

		//-----------------------------------------------------------------------------
		//static functions

	public:

		static TCameraCreationFunction GetCreationFunction();
	};
}

#endif