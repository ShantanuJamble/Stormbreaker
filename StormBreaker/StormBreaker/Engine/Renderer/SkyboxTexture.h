#ifndef SKYBOX_TEXTURE_DEF
#define SKYBOX_TEXTURE_DEF
#include "Renderer.h"
#include "framework.h"

class SkyboxTexture
{
private:
	unsigned int m_textureId;
public:
	//This needs to be handled by asset manager 
	bool LoadCubeMab(std::vector<std::string> faces);

	unsigned int  GetId() const { return m_textureId; }

	void Bind(uint8_t slot = 0);
	void Unbind();
};

#endif