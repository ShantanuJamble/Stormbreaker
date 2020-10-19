#ifndef SKYBOX_MATERIAL_H
#define SKYBOX_MATERIAL_H


#include "framework.h"
#include "SkyboxTexture.h"
#include "Material.h"




class SkyboxMaterial
{

private:
	SkyboxTexture* m_skyboxTexture;
	Shader* m_shader;

public:

	
	SkyboxMaterial(SkyboxTexture* m_skyboxTexture, Shader* m_shader);
	~SkyboxMaterial();

	inline SkyboxTexture* GetSkyboxShader() const { return m_skyboxTexture; }
	inline Shader* GetShader() const { return m_shader; }

	void BindTextures() const;
	void UnbindTextures() const;

};

#endif