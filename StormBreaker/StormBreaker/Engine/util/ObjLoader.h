#ifndef OBJLOADER_H
#define OBJLOADER_H


#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "Renderer/VertexLayout.h"

namespace util{
	void LoadOBJ(const char* filePath,
		std::vector<Vertex>& m_vertices,
		std::vector<unsigned int>& m_indices);

	

}
#endif
