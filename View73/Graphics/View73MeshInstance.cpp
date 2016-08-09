#include "View73MeshInstance.h"
#include "View73Material.h"

namespace View73
{
	MeshInstance::MeshInstance(TSharedMeshPtr _shrdMesh)
	: m_MeshPtr(_shrdMesh)
	{

	}

	MeshInstance::~MeshInstance()
	{
		m_MeshPtr.reset();
	}

	void MeshInstance::Render()
	{
		Material::defaultMaterial.ApplyMaterial();
		m_MeshPtr->Render();
	}
}