#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H


#include "framework.h"
#include "util/ObjLoader.h"
#include <unordered_map>
#include "Renderer/Mesh.h"
#include "Renderer/Material.h"
#include "Renderer/Texture.h"


namespace engine
{
	class AssetManager
	{
	private:
		static  std::unordered_map<uint8_t,Mesh*> m_MeshMap;
		static 	std::unordered_map<uint8_t,Material*> m_MaterialMap;
		static	std::unordered_map<uint8_t,Mesh*> m_TexturehMap;

	public:
		static uint8_t LoadMesh(std::string& path);
		static uint8_t LoadTexture(std::string& path);
		static uint8_t LoadMaterial(std::string& path);


		static Mesh* GetMesh(uint8_t handle);
		static Mesh* GetMaterial(uint8_t handle);
		static Mesh* GetTexture(uint8_t handle);

	};
}

#endif // !ASSET_MANAGER_H
