/********************************************************************
	filename: 	View73Light
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73Light_h__
#define __View73Light_h__

#include "../Math/View73Vector3.h"
#include "../Utils/View73String.h"
#include "../boost/smart_ptr.hpp"
#include <list>

namespace View73
{
	class Light;

	typedef boost::shared_ptr<Light> TSharedLightPtr;
	typedef std::list<TSharedLightPtr> TLightList;

	class Light
	{
	public:

		enum LightType
		{
			LT_Point,
			LT_Directional,
			LT_Spot
		};

	private:

		String m_Name;

		LightType m_LightType;

		Vector3 m_LightPos;
		Vector3 m_LightDirection;

		//Color m_AmbientColor;
		//Color m_DiffuseColor;
		//Color m_SpecularColor;

		bool m_Enabled;

		void ApplyPointLight(int _glLightID);
		void ApplyDirectionalLight(int _glLightID);
		void ApplySpotLight(int _glLightID);

	public:

		Light(const String& _name);
		~Light();

		const String& GetName();
		void SetDirection(const Vector3& _direction);
		void SetPosition(const Vector3& _position);
		void ApplyLight(int _glLightID);
	};
}

#endif