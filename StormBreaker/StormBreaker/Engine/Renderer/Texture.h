#ifndef TEXTURE_H
#define TEXTURE_H
#include "Renderer.h"
#include "framework.h"

enum TextureType { ALBEDO, NORMAL, ROUGHNESS, METALNESS };

class Texture
{

private:
	unsigned int m_RenderId;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

public:

	
	Texture() = default;
	Texture(std::string& path);
	~Texture();

	void Bind (unsigned int slot = 0) ;
	void Unbind();

	inline unsigned int GetRenderId() { return m_RenderId; }
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};

#endif