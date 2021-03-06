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

struct Attr
{
    string name;
    string val;
};

struct EltNode : public Node
{
    string tag_name;
    vector<Attr> attrs;
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
