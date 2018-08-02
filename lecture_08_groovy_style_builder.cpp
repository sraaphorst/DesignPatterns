/**
 * GROOVY-STYLE BUILDERS: DSLs
 * This shows how we can essentially build a DSL (in this case, pseudo-HTML using uniform initialization syntax.
 * Containment can be controlled as per the example.
 * This allows us to define structures in a more natural, understandable way.
 */

#include "common.h"

/**
 * HTML tag:
 * <name attribute1=value1 attribute2=value2 ...>
 *   text
 *   <children>
 * </name>
 */
struct Tag {
    string name, text;
    vector<Tag> children;
    vector<pair<string,string>> attributes;

    friend ostream &operator<<(ostream &os, const Tag &tag);

protected:
public:
    Tag(const string &name, const string &text) : name{name}, text{text} {}
    Tag(const string &name, const vector<Tag> &children) : name{name}, children{children} {}

};

/**
 * Some common tags.
 */

/**
 * A paragraph can have children: formatting, images, etc.
 * We accept these with an initialization list, which we can stick into a vector.
 */
struct P : Tag {
    P(const string &text) : Tag{"p", text} {}
    P(initializer_list<Tag> children) : Tag{"p", children} {}
};

struct IMG : Tag {
    // Only has an attribute specifying URL of image, which we need to add:
    explicit IMG(const string &url) : Tag{"img", ""} {
        attributes.emplace_back(make_pair("src", url));
    }
};
/**
 * Outputs the tag to an output stream.
 */
ostream &operator<<(ostream &os, const Tag &tag) {
    os << "<" << tag.name;
    for (const auto &attrib: tag.attributes)
        os << " " << attrib.first << "=\"" << attrib.second << "\"";

    if (tag.children.empty() && tag.text.empty())
        os << "/>" << endl;
    else {
        os << ">" << endl;

        if (!tag.text.empty())
            os << tag.text << endl;

        for (const auto &child: tag.children)
            os << child;

        os << "</" << tag.name << ">" << endl;
    }

    return os;
}

/**
 * NOTE: We have constructed OOP code that mimicks HTML, which we can even print like HTML.
 */
int main() {
    cout <<
        P { "This is Pikachu!" }
        <<
        P {
            IMG { "http://pokemon.com/pikachu.png" }
        }
        << endl;
}
