#pragma once

#include <sstream>

#include "pgr.h"

namespace sukkryst
{

	/**
	 * @brief Transform information for gameobjects
	 * 
	 */
	struct Transform
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 size;

		/**
		 * @brief Construct a new Transform object
		 * 
		 */
		Transform();

		/**
		 * @brief Construct a new Transform object
		 * 
		 * @param position new position
		 * @param rotation new rotation
		 * @param size new size
		 */
		Transform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &size);

		/**
		 * @brief Adds vector to the size
		 * 
		 * @param vector to add
		 */
		void Scale(const glm::vec3 &vector);

		/**
		 * @brief Moves the position by specific vector
		 * 
		 * @param vector to move
		 */
		void Move(const glm::vec3 &vector);

		/**
		 * @brief Rotate by specific vector
		 * 
		 * @param vector to rotate
		 */
		void Rotate(const glm::vec3 &vector);

		/**
		 * @brief Set the size to specific vector
		 * 
		 * @param vector new size
		 */
		void SetSize(const glm::vec3 &vector);

		/**
		 * @brief Set the position to specific vector
		 * 
		 * @param vector new position
		 */
		void SetPos(const glm::vec3 &vector);

		/**
		 * @brief Set the rotation to specific vector
		 * 
		 * @param vector new rotation
		 */
		void SetRot(const glm::vec3 &vector);

		/**
		 * @brief Calculates the front vector
		 * 
		 * @return glm::vec3 front 
		 */
		glm::vec3 Front() const;

		/**
		 * @brief Calculates the up vector
		 * 
		 * @return glm::vec3 up
		 */
		glm::vec3 Up() const;

		/**
		 * @brief Calculates the right vector
		 * 
		 * @return glm::vec3 right
		 */
		glm::vec3 Right() const;

		/**
		 * @brief Destroy the Transform object
		 * 
		 */
		~Transform();
	};

} // namespace sukkryst