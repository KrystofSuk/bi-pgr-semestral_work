#pragma once
#include <string>
#include <iostream>

#include "Engine/Core/component.h"
#include "Engine/Utils/printable.h"

namespace sukkryst
{

	/**
	 * @brief Debugging struct for logging
	 * 
	 */
	struct Debug
	{

		/**
		 * @brief Logging the string
		 * 
		 * @param string to print
		 */
		static void Log(const std::string &string);

		/**
		 * @brief Logging the printable object
		 * 
		 * @param printable to print
		 */
		static void Log(const Printable &printable);
	};

} // namespace sukkryst