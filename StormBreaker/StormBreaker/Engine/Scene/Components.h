#ifndef COMPOENENTS_H
#define COMPOENENTS_H

#include <glm/mat4x4.hpp>

namespace engine
{
	struct TransformComponent
	{
	public:
		glm::mat4 m_Transform;
	};


	struct LabelComponent
	{
		std::string m_label;

		LabelComponent() = default;
		LabelComponent(LabelComponent& other) = default;
		LabelComponent(const std::string& label)
			:m_label(label)
		{

		}
		~LabelComponent() = default;
		std::string GetLabel() const { return m_label; }
		void        SetLabel(const std::string& newLabel) { m_label = newLabel; }
	};
}

#endif // !COMPOENENTS_H
