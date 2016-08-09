/********************************************************************
	filename: 	View73MeshInstance
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73MeshInstance_h__
#define __View73MeshInstance_h__

#include "View73Renderable.h"
#include <list>

namespace View73
{
	class MeshInstance;

	typedef boost::shared_ptr<MeshInstance> TSharedMeshInstancePtr;
	typedef std::list<TSharedMeshInstancePtr> TMeshInstancesList;

	class MeshInstance : public Renderable
	{
	protected:

		MeshInstance(){}
		virtual ~MeshInstance(){}

	public:

		virtual void Render() = 0;
	};
}

#endif