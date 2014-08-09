#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct Node
{
    vector<Node*> children;
    enum { Text, Elt } type;
};

struct EltNode : public Node
{
    string tag_name;
    map<string, string> attr;
    EltNode() { type = Elt; }
};

struct TextNode : public Node
{
    string data;
    TextNode() { type = Text; }
};

int main()
{
    cout << "hello toy.\n";
    TextNode text1, text2;
    text1.data = "toto";
    text2.data = "titi";
    EltNode elt;
    elt.children.push_back(&text1);
    elt.children.push_back(&text2);
}
