#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include "Component.h"
#include "Renderer/Mesh.h"
#include "Renderer/Material.h"

namespace Engine {
	namespace ecs {
		struct RenderComponent : public Component
		{
		private:
			Mesh* m_mesh;
			Material* m_material;

		public:
			RenderComponent(Mesh* mesh,Material* material)
				:m_mesh(mesh),
				 m_material(material)
			{}
			// TODO: Need methods to set mesh materials at runtime so the user can try out different materials like its possible now.

		};
	}
}


#endif