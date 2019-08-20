#ifndef TEXTURE_H
#define TEXTURE_H
#include "Renderer.h"
#include "framework.h"

class Texture
{

private:
	unsigned int m_RenderId;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

public:

	static enum TextureType {ALBEDO,ROUGHNESS,METALNESS};
	Texture() = default;
	Texture(std::string& path);
	~Texture();

	void Bind (unsigned int slot = 0) ;
	void Unbind();

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};

#endif