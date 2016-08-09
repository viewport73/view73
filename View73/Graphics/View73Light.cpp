#include "View73Light.h"
#include "View73GlInclude.h"

namespace View73
{
	Light::Light(const String& _name)
		: m_Name(_name)
		, m_LightType(LT_Point)
		, m_LightDirection(Vector3(-1.0f,-1.0f,-1.0f))
		, m_LightPos(Vector3(0.0f,0.0f,0.0f))
		, m_Enabled(true)
	{
		m_LightDirection.Normalize();
	}
	
	Light::~Light()
	{

	}

	const String& Light::GetName()
	{
		return m_Name;
	}

	void Light::SetDirection(const Vector3& _direction)
	{
		m_LightDirection = _direction;
	}

	void Light::SetPosition(const Vector3& _position)
	{
		m_LightPos = _position;
	}

	void Light::ApplyLight(int _glLightID)
	{
		switch(m_LightType)
		{
		case LT_Point:
			{
				ApplyPointLight(_glLightID);
			}
			break;

		case LT_Directional:
			{
				ApplyDirectionalLight(_glLightID);
			}
			break;

		case LT_Spot:
			{
				ApplySpotLight(_glLightID);
			}
			break;
		}
	}

	void Light::ApplyPointLight(int _glLightID)
	{
		float ambientColor[4] = {0.25f,0.25f,0.25f,1.0f};
		float diffuseColor[4] = {0.75f,0.75f,0.75f,1.0f};
		float specularColor[4] = {0.0f,0.0f,0.0f,1.0f};

		glEnable(_glLightID);		
		glLightfv(_glLightID, GL_AMBIENT, ambientColor);
		glLightfv(_glLightID, GL_DIFFUSE, diffuseColor);
		glLightfv(_glLightID, GL_SPECULAR,specularColor);
		glLightfv(_glLightID, GL_POSITION, m_LightPos.GetArray());
	}

	void Light::ApplyDirectionalLight(int _glLightID)
	{
		float ambientColor[4] = {0.25f,0.25f,0.25f,1.0f};
		float diffuseColor[4] = {0.75f,0.75f,0.75f,1.0f};
		float specularColor[4] = {0.0f,0.0f,0.0f,1.0f};

		glEnable(_glLightID);		
		glLightfv(_glLightID, GL_AMBIENT, ambientColor);
		glLightfv(_glLightID, GL_DIFFUSE, diffuseColor);
		glLightfv(_glLightID, GL_SPECULAR,specularColor);
		glLightfv(_glLightID, GL_POSITION, m_LightPos.GetArray());
		glLightfv(_glLightID, GL_SPOT_DIRECTION, m_LightDirection.GetArray());
	}

	void Light::ApplySpotLight(int _glLightID)
	{
		float ambientColor[4] = {0.25f,0.25f,0.25f,1.0f};
		float diffuseColor[4] = {0.75f,0.75f,0.75f,1.0f};
		float specularColor[4] = {0.0f,0.0f,0.0f,1.0f};

		glEnable(_glLightID);		
		glLightfv(_glLightID, GL_AMBIENT, ambientColor);
		glLightfv(_glLightID, GL_DIFFUSE, diffuseColor);
		glLightfv(_glLightID, GL_SPECULAR,specularColor);
		glLightfv(_glLightID, GL_POSITION, m_LightPos.GetArray());
		glLightfv(_glLightID, GL_SPOT_DIRECTION, m_LightDirection.GetArray());
	}
}