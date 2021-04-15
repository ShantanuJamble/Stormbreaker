#ifndef UUID_COMPOENENTS_H
#define UUID_COMPOENENTS_H

#include <glm/mat4x4.hpp>
#include <string>

namespace engine
{
	namespace component
	{
		struct UUIDComponent
		{
			std::string uuid;

			UUIDComponent() = default;
			UUIDComponent(UUIDComponent& other) = default;
			UUIDComponent(const std::string& id)
				:uuid(id)
			{

			}
			~UUIDComponent() = default;
			std::string GetId() const { return uuid; }
			void        SetId(const std::string& newLabel) { uuid = newLabel; }

			operator std::string& () { return uuid; }
			operator const std::string& () const { return uuid; }
		};
	}
}

#endif