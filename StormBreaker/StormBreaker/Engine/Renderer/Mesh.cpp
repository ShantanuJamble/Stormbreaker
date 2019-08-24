#include "Mesh.h"
#include "Log.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "util/ObjLoader.h"

void Mesh::SetupMesh()
{
	m_VAO = new VertexArray();
	m_VAO->Bind();
	m_VBO = new VertexBuffer(&m_vertices[0], m_vertices.size() * sizeof(Vertex));
	m_IBO = new IndexBuffer(m_indices,m_indices.size());
	m_VAO->AddBuffer(m_VBO);
	m_VAO->Unbind();
}



Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, Material* material)
		:m_vertices(vertices), m_indices(indices), m_material(material),
		 m_VAO(nullptr), m_VBO(nullptr), m_IBO(nullptr)
{
	SetupMesh();
	SB_ENGINE_INFO("INFO: Mesh set up correctly.");
}

Mesh::Mesh(std::string& file_path, Material* material)
	:m_vertices(NULL), m_indices(NULL), m_material(material),
	m_VAO(nullptr), m_VBO(nullptr), m_IBO(nullptr)
{
	ReadFromFile(file_path);
	SetupMesh();
	SB_ENGINE_INFO("INFO: Mesh set up correctly.");
	return;
}

void Mesh::ReadFromFile(std::string& file_path)
{
	util::LoadOBJ(file_path.c_str(),
				 m_vertices,
				 m_indices);
	
	return;

}

Mesh::~Mesh()
{
	try
	{
		delete m_VAO;
		delete m_VBO;
		delete m_IBO;
		delete m_material;
	}
	catch (std::exception& e)
	{
		SB_ENGINE_ERROR("ERROR: Failed while delteing mesh. {0}", e.what());
	}
	
}
