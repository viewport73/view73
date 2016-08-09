/********************************************************************
	filename: 	View73ApplicationRoot
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73ApplicationRoot_h__
#define __View73ApplicationRoot_h__

#include "View73Application.h"

namespace View73
{
	class ApplicationRoot
	{
	private:

		class Impl;
		boost::scoped_ptr<Impl> m_Impl;

		static ApplicationRoot* m_Instance;

	private:
	
		ApplicationRoot();
		~ApplicationRoot();

	public:

		//static functions
		static void CreateInstance();
		static ApplicationRoot* Get();
		static void DestroyInstance();

		//It will release the previous application
		void SetApplicationPtr(TApplicationAutoPtr application);

		bool Update();
	};

#define gAppRoot ApplicationRoot::Get()

}

#endif