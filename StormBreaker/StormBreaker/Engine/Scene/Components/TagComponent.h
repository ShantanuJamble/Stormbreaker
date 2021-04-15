#ifndef TAG_COMPOENENTS_H
#define TAG_COMPOENENTS_H

#include <glm/mat4x4.hpp>
#include <string>

namespace engine
{
	namespace component
	{
		struct TagComponent
		{
			std::string tag;

			TagComponent() = default;
			TagComponent(TagComponent& other) = default;
			TagComponent(const std::string& label)
				:tag(label)
			{

			}
			~TagComponent() = default;
			std::string GetLabel() const { return tag; }
			void        SetLabel(const std::string& newLabel) { tag = newLabel; }

			operator std::string& () { return tag; }
			operator const std::string& () const { return tag; }

		};
		
	}
}

#endif // !COMPOENENTS_H
