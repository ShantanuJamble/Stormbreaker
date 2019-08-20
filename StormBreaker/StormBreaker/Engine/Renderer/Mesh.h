#ifndef MESH_H
#define MESH_H

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexLayout.h"
#include "Material.h"
class Mesh
{
private:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	Material* m_material;

	VertexArray* m_VAO;
	VertexBuffer* m_VBO;
	IndexBuffer* m_IBO;

	//Supporting methods
	void SetupMesh();
	void ReadFromFile(std::string& file_path);

	
public:
	Mesh(std::string& file_path,Material* material);
	Mesh(std::vector<Vertex>& vertices,
		std::vector<unsigned int>& indices,
		Material* m_material);

	~Mesh();

	inline const VertexArray* GetVertexArray() const { return m_VAO; }
	inline const IndexBuffer* GetIndexBuffer() const { return m_IBO; }
	inline const Material* GetMaterial() const { return m_material; }
};

#endif