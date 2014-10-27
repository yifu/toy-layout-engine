#include "node.hpp"

int main()
{
    TextNode text1, text2;
    text1.data = "toto";
    text2.data = "titi";
    EltNode elt1, elt2;
    elt1.tag_name = "foobar";
    elt2.tag_name = "foobar2";
    elt1.children.push_back(&text1);
    elt1.children.push_back(&text2);
    elt1.children.push_back(&elt2);
    print(&elt1);
}
