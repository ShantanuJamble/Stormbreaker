#ifndef MESH_H
#define MESH_H

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "VertexLayout.h"

class Mesh
{
private:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	Texture *m_texture;

	VertexArray* m_VAO;
	VertexBuffer* m_VBO;
	IndexBuffer* m_IBO;

	//Supporting methods
	void SetupMesh();
	void ReadFromFile(std::string& file_path);

	
public:
	Mesh(std::string& file_path,std::string& texture_path);
	Mesh(std::vector<Vertex>& vertices,
		std::vector<unsigned int>& indices,
		Texture* textures);

	~Mesh();

	inline const VertexArray* GetVertexArray() const { return m_VAO; }
	inline const IndexBuffer* GetIndexBuffer() const { return m_IBO; }
	inline const Texture*     GetTexture()	   const { return m_texture; }
};

#endif