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
			MeshComponent(MeshComponent& mesh) = default;
			
			MeshComponent(const SHARED_REF<Mesh>& other_mesh)
				:mesh(other_mesh)
			{}
		
			

			SHARED_REF<Mesh> GetMesh() { return mesh; }

			operator SHARED_REF<Mesh>& () { return mesh; }
			operator const SHARED_REF<Mesh>& () const { return mesh; }
		};

		
	}
}

#endif