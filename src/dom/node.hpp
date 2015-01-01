#ifndef DERPKIT_DOM_NODE_HPP
#define DERPKIT_DOM_NODE_HPP

#include <vector>
#include <map>
#include <memory>
#include <derpkit/export.hpp>
#include <derpkit/utils/string.hpp>
#include "css/specificity.hpp"

namespace dom {

struct NodeCSSProperty {
	const std::string& property;
	css::Specificity specificity;
};

class NodeImpl;
class DERPKIT_EXPORT Node {
public:
	Node(const char* tag);
	Node(const char* tag, const Node* parent);

	const char* get_attribute(const char* key) const;
	bool has_attribute(const char* key) const;
	void set_attribute(const char* key, const char* value);

	const std::vector<std::string>& classes() const;

	std::map<std::string,NodeCSSProperty>& css_properties();
	const char* get_css_property(const char* property) const;

	void attach(const Node* parent);
	void detach();

private:
	std::shared_ptr<NodeImpl> _impl;
};

}

#endif /* DERPKIT_DOM_NODE_HPP */
