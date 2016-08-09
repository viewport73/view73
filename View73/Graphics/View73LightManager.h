/********************************************************************
	filename: 	View73LightManager
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73LightManager_h__
#define __View73LightManager_h__

#include "../boost/smart_ptr.hpp"
#include <list>
#include "View73Light.h"

namespace View73
{
	class LightManager
	{
	public:
		friend class GraphicsRoot;

		typedef std::list<TSharedLightPtr> TSharedLightPtrList;

	private:

		class Impl;
		boost::scoped_ptr<Impl> m_Impl;

		static LightManager *m_Instance;

	private:

		//--------------------------------------------------------------------
		//Static functions
		static void CreateInstance();
		static void DestroyInstance();
		//--------------------------------------------------------------------

		LightManager();
		~LightManager();

	public:

		//--------------------------------------------------------------------
		//Static functions
		static LightManager* Get();
		//--------------------------------------------------------------------

		void ClearAllLight();

		TSharedLightPtr CreateLight(const String& _lightName);
		TSharedLightPtr GetLight(const String& _lightName);
		void DestroyLight(const String& _lightName);

	};

	#define gLightManager LightManager::Get()
}

#endif