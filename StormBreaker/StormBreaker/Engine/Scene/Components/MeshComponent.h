#ifndef MESH_COMPOENENTS_H
#define MESH_COMPOENENTS_H

#include "Core/Core.h"
#include "Renderer/Material.h"
#include "Renderer/Mesh.h"


namespace engine
{
	namespace component
	{
		struct MeshComponent
		{
			SHARED_REF<Mesh> mesh;

			MeshComponent() = default;
			MeshComponent(const MeshComponent& mesh) = default;
			MeshComponent(MeshComponent&& other) = default;
			MeshComponent& operator=(MeshComponent&& other) = default;
			MeshComponent(const SHARED_REF<Mesh>& other_mesh)
				:mesh(other_mesh)
			{}
		
			

			SHARED_REF<Mesh> GetMesh() { return mesh; }
		};

		
	}
}

#endif