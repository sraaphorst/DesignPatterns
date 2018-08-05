/**
 * BUILDER: when construction gets a bit too complicated.
 *
 * Examples: StringBuilder, which allows you to construct an object piece-by-piece.
 *
 * Having an object with 10 constructor arguments is not productive.
 * Instead of huge constructors. opt for piecewise construction via a special API.
 *
 * In this example, assume we are working on a backend web server, which serves a certain amount of HTML.
 * Begin by assuming we will make strings we are going to return.
 */

#include "common.h"
int main() {
    /**
     * This works, but this approach doesn't scale.
     */
    auto text = "hello";
    string output;
    output += "<p>";
    output += text;
    output += "</p>";
    cout << output << endl;

    /**
     * Say you want to output a bunch of list items. You wouldn't use string concat.
     * This is a better approach, but is becoming more complicated.
     */
     string words[] = { "hello", "world", "from", "Fayfay" };
     ostringstream oss;
     oss << "<ul>" << endl;
     for (const auto &w : words)
         oss << "\t<li>" << w << "</li>" << endl;
     oss << "</ul>" << endl;
     cout << oss.str();

     /**
      * In HTML, there are all sorts of rules about what tags can contain other tags and tag nesting, etc.
      * None of this is being enforced here.
      *
      * With the Builder pattern, instead of building these rinky-dink string out of these silly concatenations, you
      * instead define some OOP structure which supports its transformation to a string.
      */
}
