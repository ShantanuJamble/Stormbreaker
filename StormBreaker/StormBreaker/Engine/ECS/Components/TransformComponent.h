#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "Component.h"
#include "glm/glm.hpp"
#include "glm/vec4.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/matrix_inverse.hpp"

namespace Engine {
	namespace ecs {
		struct Transform : public Component
		{

		private:
			bool m_updateFlag; 

			glm::vec3 m_front;
			glm::mat4 m_model; //* The model matrix of the transform
			glm::mat3 m_normal; //* The normal matrix of the transform
			glm::vec3 m_position; //* The position of the Tranform
			glm::vec3 m_scale; //* The scale of the transform
			glm::quat m_rotation; //* The rotation of the transform
			glm::mat4 m_parentMatrix;//matrix of parent in world Space


			/**
			* Recalculates the world matrix
			 */
			void RecalculateMatrix()
			{
				//m_model = m_parentMatrix *glm::mat4(1.0f) ;
				m_model = glm::translate(m_parentMatrix, m_position);
				m_model *= glm::mat4_cast(m_rotation);
				m_model = glm::scale(m_model, m_scale);

				m_normal = glm::mat3(glm::inverseTranspose(m_model));
				//m_front *= m_rotation;
				//m_updated = true;
				m_updateFlag = false;
			}

		public:
			Transform()
				:m_position({ 0.0f, 0.0f, 0.0f }), m_rotation(glm::quat()), m_scale({ 1.0f,1.0f,1.0f }), m_model(1.0f),
				m_normal(1.0f), m_updateFlag(true), m_parentMatrix(glm::mat4(1.0)), m_front({ 1.0f, 0.0f, 0.0f })
			{
				RecalculateMatrix();
			}

			Transform(glm::vec3 pos, glm::quat rot, glm::vec3 scale)
				: m_position(pos), m_rotation(rot), m_scale(scale), m_updateFlag(true),
				m_parentMatrix(glm::mat4(1.0)), m_front({ 1.0f, 0.0f, 0.0f })
			{
				RecalculateMatrix();
			}



			inline const bool GetFlag() const { return m_updateFlag; }
			inline void SetPosition(const glm::vec3& pos) { m_position = pos; m_updateFlag = true; }// m_updateFlag = true; }
			inline void SetRotation(const glm::quat& rot) { m_rotation = rot; m_updateFlag = true; }//m_updateFlag = true; }
			inline void SetScale(const glm::vec3& scale) { m_scale = scale; m_updateFlag = true; }//m_updateFlag = true; }

			inline const glm::vec3& GetFront() const { return m_front; }
			inline const glm::vec3& GetPosition() const { return m_position; }
			inline const glm::quat& GetRotation() const { return m_rotation; }
			inline const glm::vec3& GetScale() const { return m_scale; }
			inline const glm::mat4& GetModel() const { return m_model; }
			inline const glm::mat3& GetNormal() const { return m_normal; }

			void CheckFlag()
			{
				if (m_updateFlag)
					RecalculateMatrix();
			}

			// Methods useful for the scene 
			//Can be used when setting up parent in a scene
			inline void SetRelativeSpace(glm::mat4 parentMatrix)
			{
				m_parentMatrix = parentMatrix; m_updateFlag = true;
			}
			inline const glm::vec3 GetRelativePosition() const { return glm::vec3(m_parentMatrix * glm::vec4(m_position, 1.0)); }
			const glm::vec3 GetRelativeScale() const
			{
				glm::vec3 scale = glm::vec3(m_parentMatrix * glm::vec4(m_scale, 1.0));
				return scale;
			}
		};
	}
}

#endif