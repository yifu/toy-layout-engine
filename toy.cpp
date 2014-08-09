#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

enum NodeType { Text, Elt };

struct Node
{
    vector<Node*> children;
    NodeType type;
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

// TODO Better to implement the pretty printing as a virtual method in
// each structs.

void print(Node *node, int indent = 0, string eol = "\n")
{
    if(node == 0)
    {
	cout << string(indent, ' ');
	cout << "[]" << eol;
	return;
    }
    if(node->type == Text)
    {
       	cout << string(indent, ' ');
	cout << "TextNode[\n";
	indent += 2;
       	cout << string(indent, ' ');
	cout << "data=\"" << ((TextNode*)node)->data << "\",\n";
    }
    else if(node->type == Elt)
    {
	cout << string(indent, ' ');
	cout << "EltNode[\n";
	indent += 2;
	cout << string(indent, ' ');
	cout << "tag name=" << ((EltNode*)node)->tag_name << ",\n";
	// TODO print attr fields.
    }
    if(node->children.size() > 0)
    {
	cout << string(indent, ' ');
	cout << "children=[\n";
	for(size_t i = 0; i < node->children.size(); ++i)
	{
	    string eol = (i != node->children.size()-1)? ",\n" : "\n";
	    print(node->children[i], indent+2, eol);
	}
	cout << string(indent, ' ');
	cout << "]\n";
    }
    indent -= 2;
    cout << string(indent, ' ');
    cout << "]" << eol;
}

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
