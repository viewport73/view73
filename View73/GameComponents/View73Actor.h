/********************************************************************
	filename: 	View73Actor
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Actor_h__
#define __View73Actor_h__

#include "../boost/smart_ptr.hpp"
#include <boost/function.hpp>
#include "../Graphics/View73FrameEvent.h"
#include "../Math/View73Vector3.h"
#include "../Math/View73Quaternion.h"
#include "../View73BulletPhysics/View73BulletTypes.h"
#include "../Utils/View73String.h"

namespace View73
{
	class Actor;
	typedef boost::shared_ptr<Actor> TActorSharedPtr;
	typedef boost::weak_ptr<Actor> TActorWeakPtr;
	typedef std::auto_ptr<Actor> TActorAutoPtr;

	typedef boost::function<TActorSharedPtr ()> TActorToken;

	class Actor
	{
	private:

		const unsigned int m_InteractiveActorType;
		const String m_ActorName;

	public:

		Actor(unsigned int _actorType, const String& _actorName)
			: m_InteractiveActorType(_actorType)
			, m_ActorName(_actorName)
		{
		}

		virtual ~Actor(){}

		unsigned int GetInteractiveActorType() const	{	return m_InteractiveActorType;	}
		const String& GetName() const				{	return m_ActorName;				}

		virtual void SetPosition(const Vector3& _pos) = 0;
		virtual const Vector3& GetPosition() const = 0;
		virtual const Quaternion& GetRotation() const = 0;
		
		virtual void Update(const FrameEvent& _frameEvent) = 0;
		
		virtual TCollisionObjectWeakPtr GetCollisionObject() = 0;

		virtual bool TokenizeActor() const = 0;
		virtual TActorToken GetActorToken() const = 0;

		virtual void Reset() {}
	};
}

#endif