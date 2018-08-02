#include "common.h"

/**
 * BUILDER
 *
 * Start off by creating OOP parts to define the different parts you are building.
 * For example, in our case, we have a top-level HTML element.
 */

/**
 * This is just a way to model an HTML element via OOP.
 * The actual builder is below.
 */
struct HtmlElement {
    string name, text;
    vector<HtmlElement> elements;

    // Define indentation size.
    const size_t indent_size = 2;

    HtmlElement() {}

    Htm                         << endl;
        if (!text.empty())
            oss << string(indent_size * (indent + 1), ' ') << text << endl;

        for (const auto &e: elements)
            oss << e.str(indent + 1);

        oss << i << "</" << name << ">" << endl;
        return oss.str();
    }
};


/**
 * The builder.
 *
 * It will allow us to define the root of our element, and then add children in a simple fashion.
 * Note that we are using the HtmlBuilder to build up our much more complex HtmlElement object.
 *
 * Instead of creating the object in a single line, we are doing so piece-wise with special components that
 * help us at each step of the way.
 *
 * After the construction, you call the appropriate function (here: str) to get whatever is it you've constructed.
 */
struct HtmlBuilder {
    HtmlElement root;

    /**
     * Constructor: inconvenient to work with HTML elements. Just want to work with strings.
     *
     * If someone wants a string UL in here, they can just pass that.
     */
    HtmlBuilder(string rootName) {
        root.name = rootName;
    }

    /**
     * Add children: create new HtmlElement and make it a child.
     */
     void addChild(string childName, string childText) {
         HtmlElement e{childName, childText};
         root.elements.emplace_back(e);
     }

     /**
      * An str function to show what we've actually built.
      */
    string str() const {
        return root.str();
    }
};



int main() {
//    auto text = "hello";
//    string output;
//    output += "<p>";
//    output += text;
//    output += "</p>";
//
//    string words[] = { "hello", "world", "from", "Fayfay" };
//    ostringstream oss;
//    oss << "<ul>" << endl;
//    for (const auto &w : words)
//        oss << "\t<li>" << w << "</li>" << endl;
//    oss << "</ul>" << endl;
//    cout << oss.str();

    /**
     * Now, instead, we use the HTML builder.
     * The goal is not the formatting so much as the fact that we're using OOP structures to define everything.
     */
    HtmlBuilder builder{"ul"};
    builder.addChild("li", "hello");
    builder.addChild("li", "world");
    builder.addChild("li", "from");
    builder.addChild("li", "Fayfay");
    cout << builder.str() << endl;
}