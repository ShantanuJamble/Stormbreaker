#ifndef COMPOENENTS_H
#define COMPOENENTS_H

#include <glm/mat4x4.hpp>
#include <string>

namespace engine
{
	namespace component
	{
		struct TagComponent
		{
			std::string m_label;

			TagComponent() = default;
			TagComponent(TagComponent& other) = default;
			TagComponent(const std::string& label)
				:m_label(label)
			{

			}
			~TagComponent() = default;
			std::string GetLabel() const { return m_label; }
			void        SetLabel(const std::string& newLabel) { m_label = newLabel; }
		};
	}
}

#endif // !COMPOENENTS_H
