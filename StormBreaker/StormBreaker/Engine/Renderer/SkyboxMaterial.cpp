#include "SkyboxMaterial.h"
#include "Log.h"

SkyboxMaterial::SkyboxMaterial(SkyboxTexture* skyboxTexture, Shader* shader)
	:m_skyboxTexture(skyboxTexture),m_shader(shader)
{
}

SkyboxMaterial::~SkyboxMaterial()
{
	try {
		if (m_skyboxTexture)
			delete m_skyboxTexture;
	}
	catch (std::exception& e)
	{
		SB_ENGINE_ERROR("ERROR: Error while deleting skybox material. {0}", e.what());
	}
}

void SkyboxMaterial::BindTextures() const
{
	m_skyboxTexture->Bind();
}

void SkyboxMaterial::UnbindTextures() const
{
	m_skyboxTexture->Unbind();
}
