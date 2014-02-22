#ifndef CSS_RULE_HPP
#define CSS_RULE_HPP

#include <vector>
#include "cssselector.hpp"
#include "cssproperty.hpp"

class CSSRule {
	public:
		/**
		 * Debug print
		 */
		void print(int indent=0) const;

	private:
		std::vector<CSSSelectorGroup> m_selectors;
		std::vector<CSSProperty> m_properties;

		friend class CSS;
};

#endif