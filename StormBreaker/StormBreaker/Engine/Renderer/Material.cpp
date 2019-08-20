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
	delete m_shader;
	delete m_albedoTexture;
}

void Material::SetTexture(Texture* texture, Texture::TextureType type)
{
	if (texture == nullptr)
	{
		SB_ENGINE_ERROR("ERROR: Texture pointer invalid or null.");
		return;
	}
	switch (type)
	{
		case  Texture::TextureType::ALBEDO :
			
			m_albedoTexture = texture;
			break;

		case Texture::TextureType::METALNESS:
			break;

		case Texture::TextureType::ROUGHNESS:
			break;
	}
}

void Material::SetTexture(std::string& texturePath, Texture::TextureType type)
{
	
	Texture* texture = new Texture(texturePath);
	switch (type)
	{
	case  Texture::TextureType::ALBEDO:

		m_albedoTexture = texture;
		break;

	case Texture::TextureType::METALNESS:
		break;

	case Texture::TextureType::ROUGHNESS:
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
