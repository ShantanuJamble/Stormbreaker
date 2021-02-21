/***
	* Should seperate components like we did in Falcon.
	***/


#include <glm/mat4x4.hpp>

namespace engine {

	namespace component 
	{
		struct TransformComponent
		{
		public:
			glm::mat4 m_Transform;
		};
	}
}
