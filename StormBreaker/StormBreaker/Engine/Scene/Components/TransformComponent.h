#ifndef TRANSFORM_COMPOENENTS_H
#define TRANSFORM_COMPOENENTS_H


#include <glm/mat4x4.hpp>

namespace engine {

	namespace component 
	{
		struct TransformComponent
		{
			glm::mat4 transform;

			TransformComponent() = default;
			TransformComponent(TransformComponent& ) = default;

			TransformComponent(glm::mat4& transform)
				:transform(transform){}

			operator glm::mat4& () { return transform; }
			operator const glm::mat4& () const { return transform; }

			//Should add a decopose method.

		};
	}
}

#endif