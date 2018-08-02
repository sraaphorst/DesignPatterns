#include "lecture_07_fluent_builder.h"

string HtmlElement::str(int indent) const {
    ostringstream oss;
    string i(indent_size * indent, ' ');

    oss << i << "<" << name << ">" << endl;
    if (!text.empty())
        oss << string(indent_size * (indent + 1), ' ') << text << endl;

    for (const auto &e: elements)
        oss << e.str(indent + 1);

    oss << i << "</" << name << ">" << endl;
    return oss.str();
}

/**
 * The starting point for creating an HtmlElement.
 */
HtmlBuilder HtmlElement::create(const string &root_name) {
    return {root_name};
}

/**
 * CLion incorrectly says this is not being used: it is implicitly being used in the HtmlElement::create method.
 */
HtmlBuilder::HtmlBuilder(const string &root_name) {
    root.name = root_name;
}

HtmlBuilder &HtmlBuilder::addChild(const string &childName, const string &childText) {
    HtmlElement e{childName, childText};
    root.elements.emplace_back(e);
    return *this;
}

string HtmlBuilder::str() const {
    return root.str();
}

int main() {
    /**
     * We now force the user to use the HtmlBuilder.
     * Neither HtmlElements not HtmlBuilders can be explicitly created. The workflow is as follows in the two
     * examples, both of which work.
     */

    /**
     * HtmlBuilder created by HtmlElement::create.
     * Completed HtmlElement obtained by conversion operator.
     */
    HtmlElement elem = HtmlElement::create("ul")
            .addChild("li", "hello")
            .addChild("li", "word")
            .addChild("li", "from")
            .addChild("li", "Fayfay");
    cout << elem.str() << endl;

    /**
     * HtmlBuilder created by HtmlElement::create.
     * Completed HtmlElement obtained by HtmlBuilder::build element.
     */
    HtmlElement cats = HtmlElement::create("ol")
        .addChild("li", "Yags")
        .addChild("li", "Fifi")
        .addChild("li", "MAX")
        .addChild("li", "The other one").build();
    cout << cats.str() << endl;
}