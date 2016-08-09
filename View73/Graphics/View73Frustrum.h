/********************************************************************
	filename: 	View73Frustrum
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Frustrum_h__
#define __View73Frustrum_h__

//#include "../boost/smart_ptr.hpp"
#include "View73SceneManager.h"
#include "../Math/View73Matrix44.h"
#include "../Math/View73Vector3.h"
#include "../Math/View73Vector2.h"
#include <boost/function.hpp>
#include "View73OnRenderListener.h"

namespace View73
{
	class Frustrum;

	typedef boost::shared_ptr<Frustrum> TSharedFrustrumPtr;
	typedef boost::weak_ptr<Frustrum> TFrustrumWeakPtr;
	
	class Frustrum
	{
	public:

		friend class Viewport;

		enum ProjectionType
		{
			ePT_ORTHOGRAPHIC,
			ePT_PERSPECTIVE
		};

	private:

		const String m_Name;
	
		const ProjectionType m_ProjType;

		// y-direction field-of-view in radians
		float m_FOVy ;

		float m_TanHalfFOVy;

		// Far clip distance
		float m_FarDist;

		// Near clip distance
		float m_NearDist;

		// x/y viewport ratio
		float m_Aspect;

		float m_FocalLength;
	    
		
		bool m_DirtyProjectionParameters;
		float m_Left, m_Right, m_Top, m_Bottom;

		bool m_CustomProjParams;		
	    
		bool m_DirtyProjectionMatrix;
		Matrix44 m_ProjMatrix;
		Matrix44 m_InvProjMatrix;

		// frustum center offset
		Vector2 m_FrustumOffset;
	    
		float	m_OrthoHeight;

		TOnRenderListenerWeakPtrList m_OnRenderListeners;


	protected:

		TSharedSceneManagerPtr m_SceneManager;

	public:

		Frustrum(const String& _name,ProjectionType _projType,TSharedSceneManagerPtr _sceneManager)
			: m_Name(_name)
			, m_ProjType(_projType)
			, m_DirtyProjectionParameters(true)
			, m_DirtyProjectionMatrix(true)
			, m_FOVy(kPI/4)//45 degrees
			, m_TanHalfFOVy(tan(m_FOVy * 0.5f))
			, m_FarDist(100.0f)
			, m_NearDist(1.0f)
			, m_Aspect(1.3333f)
			, m_CustomProjParams(false)
			, m_FocalLength(1.0f)
			, m_FrustumOffset(Vector2::ZERO)
			, m_OrthoHeight(10)
			, m_SceneManager(_sceneManager)
		{
		}

		virtual ~Frustrum()
		{
			m_OnRenderListeners.clear();
		}

		inline const String& GetName()	{	return m_Name;		}

		inline void SetViewportAspectRatio(float _aspectRatio)
		{
			m_Aspect = _aspectRatio;
			m_DirtyProjectionParameters = true;
		}

		inline void SetFarClipDistance(float _distance)
		{
			m_FarDist = _distance;
			m_DirtyProjectionParameters = true;
		}

		inline void SetNearClipDistance(float _distance)
		{
			m_NearDist = _distance;
			m_DirtyProjectionParameters = true;
		}

		const Matrix44& GetProjectionMatrix()
		{
			UpdateProjectionParameters();
			UpdateProjectionMatrix();
			return m_ProjMatrix;
		}

		inline const Matrix44& GetInverseProjectionMatrix()
		{
			UpdateProjectionParameters();
			UpdateProjectionMatrix();
			return m_InvProjMatrix;
		}

		inline void SetCustomProjeParams(float _left, float _right, float _bottom, float _top)
		{
			m_CustomProjParams = true;
			m_Left   = _left;
			m_Right  = _right;
			m_Bottom = _bottom;
			m_Top    = _top;
			m_DirtyProjectionParameters = false;
			m_DirtyProjectionMatrix = true;
		}

		inline void SetCustomProjectionParamsToFalse()
		{
			m_CustomProjParams = false;
			m_DirtyProjectionParameters = true;
			m_DirtyProjectionMatrix = true;
		}

		inline void AddOnRenderListener(TOnRenderListenerWeakPtr _listener)
		{
			m_OnRenderListeners.push_back(_listener);
		}

		inline float GetFOVY() const						{	return m_FOVy;						}
		inline float GetTanHalfFOVY() const				{	return m_TanHalfFOVy;				}

		virtual const Matrix44& GetViewMatrix()			{	return Matrix44::IDENTITY;		}
		virtual const Matrix44& GetInverseViewMatrix()	{	return Matrix44::IDENTITY;		}

	protected:

		void SetProjectionMatrix();

	private:

		void UpdateScene();
		virtual void OnRenderStart() = 0;
		void RenderScene();
		virtual void OnRenderEnd() = 0;
	
		void UpdateProjectionParameters();
		void UpdateProjectionMatrix();
		void LoadProjectionMatrixToGL();
		void CallListenerOnRenderFinished();
	};

	typedef boost::function<TSharedFrustrumPtr (const String&, Frustrum::ProjectionType,TSharedSceneManagerPtr )> TCameraCreationFunction;

}

#endif