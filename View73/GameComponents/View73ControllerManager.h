/********************************************************************
	filename: 	View73ControllerManager
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73ControllerManager_h__
#define __View73ControllerManager_h__

#include "View73Controller.h"
#include <list>

namespace View73
{
	class ControllerManager
	{
	public:

		typedef std::list<TControllerSharedPtr> TControllerSharedPtrList;

	private:

		static ControllerManager *m_Instance;

		TControllerSharedPtrList m_AllControllers;

	public:

		//--------------------------------------------------------------------
		//Static functions
		static void CreateInstance();
		static void DestroyInstance();
		static ControllerManager* Get();
		//--------------------------------------------------------------------

		ControllerManager();
		~ControllerManager();

		void AddController(TControllerSharedPtr _newController);
		void ClearAllControllers();
		void Update(const FrameEvent& _frameEvent);

	};

#define gControllerManager ControllerManager::Get()
}

#endif