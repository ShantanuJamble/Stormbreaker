#ifndef MATERIAL_H
#define MATERIAL_H


#include "framework.h"
#include "Texture.h"
#include "Material.h"




class Material
{

private:
	Texture* m_albedoTexture;
	Texture* m_normalTexture;
	//Texture* m_normalTexture;
	Shader*  m_shader;

public:

	Material();
	Material(Texture* albedo, Texture* normal,Shader* shader);
	Material(std::string& albedoTexturePath, std::string& normalTexturePath, Shader* shader);
	~Material();
	void SetTexture(Texture* texture, TextureType type);
	void SetTexture(std::string& texturePath, TextureType type);
	void SetShader(Shader* shader);

	inline Texture* GetTexture() const { return m_albedoTexture; }
	inline Shader* GetShader() const { return m_shader; }

	void BindTextures() const;
	void UnBindTextures() const;

};

#endif