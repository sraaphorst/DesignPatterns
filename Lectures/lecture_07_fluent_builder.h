#pragma once

#include <common.h>

/**
 * FLUENT FORCED BUILDER
 * We now force the user to use the HtmlBuilder and not the HtmlElement.
 *
 * WORKFLOW:
 * 1. Call object::create(...) to get objectbuilder
 * 2. Invoke objectbuilder methods to configure object.
 * 3. Call objectbuilder::build() (or use operating overloading) to get the final object.
 */

// Class forward.
class HtmlBuilder;

/**
 * Users cannot directly create HtmlElement: they must use the builder obtained by HtmlElement::create().
 */
class HtmlElement {
    friend class HtmlBuilder;

private:
    string name, text;
    vector<HtmlElement> elements;

    // Define indentation size.
    const size_t indent_size = 2;

    HtmlElement() {}

    HtmlElement(string name, string text) : name(std::move(name)), text(std::move(text)) {}

public:
    /**
     * Print it. The building up of these elements is where the builder element comes into play.
     * Note that the indentation level increases as you go.
     */
    string str(int indent = 0) const;

    /**
     * Easy way to convert from an HtmlElement to an HtmlBuilder.
     */
    static HtmlBuilder create(const string &root_navme);
};


/**
 * The fluent builder.
 *
 * It allows us to build our object in a flow-like fashion.
 * The builder should not be directly constructable.
 *
 * When the building is done, build is invoked to get the built object.
 */
class HtmlBuilder {
    friend class HtmlElement;

private:
    HtmlElement root;

    /**
     * Constructor: inconvenient to work with HTML elements. Just want to work with strings.
     *
     * If someone wants a string UL in here, they can just pass that.
     */
    HtmlBuilder(const string &rootName);

public:
    /**
     * Add children: create new HtmlElement and make it a child.
     * NOTE: instead of void, we now return this.
     */
    HtmlBuilder &addChild(const string &childName, const string &childText);

    /**
     * CONVERSION OPERATOR!
     * This allows us to automatically convert an HtmlBuilder to an HtmlElement.
     * See the end of main in the cpp file.
     *
     * If this is the last thing you will do, you can move the root out of here using
     * std::move to avoid copying.
     */
    operator HtmlElement() const {
        return std::move(root);
    }

    /**
     * An str function to show what we've actually built.
     * This does the same thing as HtmlElement.str.
     */
    string str() const;

    /**
     * Returns the built HtmlElement once you are done with the builder.
     */
    HtmlElement build() { return root; }
};
