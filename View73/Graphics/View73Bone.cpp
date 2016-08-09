#include "View73Bone.h"

namespace View73
{
	Bone::Bone(const String& _name, unsigned int _index)
		: Node(eNT_Bone,_name)
		, m_Index(_index)
	{

	}

	Bone::~Bone()
	{

	}

}