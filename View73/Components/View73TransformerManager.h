/********************************************************************
	filename: 	View73TransformerManager
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73TransformerManager_h__
#define __View73TransformerManager_h__

#include "View73Transformer.h"
#include <list>

namespace View73
{
	class TransformerManager
	{
	public:

		typedef std::list<TTransformerSharedPtr> TTransformerPtrList;
		typedef TTransformerPtrList::iterator TTransformerPtrListItr;

	private:

		static TransformerManager *m_Instance;

		TTransformerPtrList m_AllTransformers;

	public:


		//--------------------------------------------------------------------
		//Static functions
		static void CreateInstance();
		static void DestroyInstance();
		static TransformerManager* Get();
		//--------------------------------------------------------------------

		TransformerManager();
		~TransformerManager();

		void ClearAllTransformers();

		TTransformerSharedPtr AddTransformer(TTransformerAutoPtr _transformer);
		void DestroyTransformer(TTransformerPtrListItr _transformer);

		void Update(const FrameEvent& _frameEvent);
	};

#define gTransformerManager TransformerManager::Get()
}

#endif