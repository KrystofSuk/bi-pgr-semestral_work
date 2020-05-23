#pragma once

#include <string>

namespace sukkryst
{

	/**
	 * @brief Pritable object dependency
	 * 
	 */
	struct Printable
	{

		/**
		 * @brief Abstraction of print method for print required objects
		 * 
		 * @return std::string printed text
		 */
		virtual std::string Print() const { return ""; };
	};

} // namespace sukkryst