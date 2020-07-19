#include "Material.h"
#include "Log.h"

Material::Material()
	:m_albedoTexture(nullptr),
	 m_normalTexture(nullptr),
	 m_shader(nullptr)
{
	
}

Material::Material(Texture* albedo, Texture* normal, Shader* shader)
	:m_albedoTexture(albedo),
	 m_normalTexture(normal),
	 m_shader(shader)
{

}

Material::Material(std::string& albedoTexturePath, std::string& normalTexturePath, Shader* shader)
	:m_albedoTexture(new Texture(albedoTexturePath)),
	 m_normalTexture(new Texture(normalTexturePath)),
	 m_shader(shader)
{

}

Material::~Material()
{

	try {
		if (m_shader)
			delete m_shader;
		if (m_albedoTexture)
			delete m_albedoTexture;
		if (m_albedoTexture)
			delete m_normalTexture;
	}
	catch (std::exception& e)
	{
		SB_ENGINE_ERROR("ERROR: Error while deleting material. {0}", e.what());
	}
}

void Material::SetTexture(Texture* texture, TextureType type)
{
	if (texture == nullptr)
	{
		SB_ENGINE_ERROR("ERROR: Texture pointer invalid or null.");
		return;
	}
	switch (type)
	{
		case  TextureType::ALBEDO :
			m_albedoTexture = texture;
			break;
		case  TextureType::NORMAL:
			m_normalTexture= texture;
			break;
		case TextureType::METALNESS:
			break;

		case TextureType::ROUGHNESS:
			break;
	}
}

void Material::SetTexture(std::string& texturePath, TextureType type)
{
	Texture* texture = nullptr;
	try {
		switch (type)
		{
		case  TextureType::ALBEDO:
			if(m_albedoTexture)
				delete m_albedoTexture;
			texture = new Texture(texturePath);
			m_albedoTexture = texture;
			break;
		case  TextureType::NORMAL:
			if (m_normalTexture)
				delete m_normalTexture;
			texture = new Texture(texturePath);
			m_normalTexture = texture;
			break;
		case TextureType::METALNESS:
			break;

		case TextureType::ROUGHNESS:
			break;
		}
	}
	catch (std::exception& e)
	{
		SB_ENGINE_ERROR("ERROR: Failed to create {0} texture. \n {1}", type, e.what());
		return;
	}
}

void Material::SetShader(Shader* shader)
{
	if (shader == nullptr)
	{
		SB_ENGINE_ERROR("ERROR: Shader pointer invalid or null.");
		return;
	}

	m_shader = shader;
}

void Material::BindTextures() const
{
	m_albedoTexture->Bind(0);
	m_normalTexture->Bind(1);
}

void Material::UnBindTextures() const
{
	m_albedoTexture->Unbind();
	m_normalTexture->Unbind();
}
