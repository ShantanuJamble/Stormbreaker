#ifndef MATERIAL_H
#define MATERIAL_H


#include "framework.h"
#include "Texture.h"
#include "Material.h"


class Material
{

private:
	Texture* m_albedoTexture;
	Shader*  m_shader;

public:

	Material();
	Material(Texture* albedo, Shader* shader);
	Material(std::string& albedoTexturePath, Shader* shader);
	~Material();
	void SetTexture(Texture* texture, TextureType type);
	void SetTexture(std::string& texturePath, TextureType type);
	void SetShader(Shader* shader);

	inline Texture* GetTexture() const { return m_albedoTexture; }
	inline Shader* GetShader() const { return m_shader; }

};

#endif