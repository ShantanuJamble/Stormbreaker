#include "Material.h"
#include "Log.h"

Material::Material()
	:m_albedoTexture(nullptr),
	 m_shader(nullptr)
{
	
}

Material::Material(Texture* albedo, Shader* shader)
	:m_albedoTexture(albedo),
	 m_shader(shader)
{

}

Material::Material(std::string& albedoTexturePath, Shader* shader)
	:m_albedoTexture(new Texture(albedoTexturePath)),
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

		case TextureType::METALNESS:
			break;

		case TextureType::ROUGHNESS:
			break;
	}
}

void Material::SetTexture(std::string& texturePath, TextureType type)
{
	
	Texture* texture = new Texture(texturePath);
	switch (type)
	{
	case  TextureType::ALBEDO:

		m_albedoTexture = texture;
		break;

	case TextureType::METALNESS:
		break;

	case TextureType::ROUGHNESS:
		break;
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
