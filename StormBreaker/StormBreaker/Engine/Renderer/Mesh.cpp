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
	//Calculate tangents and binormals
	CalculateTangents();
	SetupMesh();
	SB_ENGINE_INFO("INFO: Mesh set up correctly.");
}

Mesh::Mesh(std::string& file_path, Material* material)
	:m_vertices(NULL), m_indices(NULL), m_material(material),
	m_VAO(nullptr), m_VBO(nullptr), m_IBO(nullptr)
{
	ReadFromFile(file_path);
	//Calculate tangents and binormals
	CalculateTangents();
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



// Calculates the tangents of the vertices in a mesh
// Code adapted from: http://www.terathon.com/code/tangent.html
void Mesh::CalculateTangents()
{
	float numVerts = m_vertices.size();
	// Reset tangents
	for (int i = 0; i < numVerts; i++)
	{

		m_vertices[i].Tangent = glm::vec3(0, 0, 0);
	}

	// Calculate tangents one whole triangle at a time
	for (int i = 0; i < numVerts;)
	{
		// Grab indices and vertices of first triangle
		unsigned int i1 = m_indices[i++];
		unsigned int i2 = m_indices[i++];
		unsigned int i3 = m_indices[i++];
		Vertex* v1 = &m_vertices[i1];
		Vertex* v2 = &m_vertices[i2];
		Vertex* v3 = &m_vertices[i3];

		// Calculate vectors relative to triangle positions
		float x1 = v2->Position.x - v1->Position.x;
		float y1 = v2->Position.y - v1->Position.y;
		float z1 = v2->Position.z - v1->Position.z;

		float x2 = v3->Position.x - v1->Position.x;
		float y2 = v3->Position.y - v1->Position.y;
		float z2 = v3->Position.z - v1->Position.z;

		// Do the same for vectors relative to triangle uv's
		float s1 = v2->TexCoords.x - v1->TexCoords.x;
		float t1 = v2->TexCoords.y - v1->TexCoords.y;

		float s2 = v3->TexCoords.x - v1->TexCoords.x;
		float t2 = v3->TexCoords.y - v1->TexCoords.y;

		// Create vectors for tangent calculation
		float r = 1.0f / (s1 * t2 - s2 * t1);

		float tx = (t2 * x1 - t1 * x2) * r;
		float ty = (t2 * y1 - t1 * y2) * r;
		float tz = (t2 * z1 - t1 * z2) * r;

		// Adjust tangents of each vert of the triangle
		v1->Tangent.x += tx;
		v1->Tangent.y += ty;
		v1->Tangent.z += tz;

		v2->Tangent.x += tx;
		v2->Tangent.y += ty;
		v2->Tangent.z += tz;

		v3->Tangent.x += tx;
		v3->Tangent.y += ty;
		v3->Tangent.z += tz;
	}

	// Ensure all of the tangents are orthogonal to the normals
	for (int i = 0; i < numVerts; i++)
	{
		// Grab the two vectors
		glm::vec3 normal = m_vertices[i].Normal;
		glm::vec3 tangent = m_vertices[i].Tangent;

		// Use Gram-Schmidt orthogonalize
		tangent = glm::normalize(tangent - normal * glm::dot(normal, tangent));

		// Store the tangent
		m_vertices[i].Tangent = tangent;
	}


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
