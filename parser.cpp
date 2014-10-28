
#include <iostream>
#include <fstream>
#include <string>
#include "node.hpp"
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

ifstream file("./test.html");

vector<Node *> parseNodes();

void skipWS()
{
    cout << "skip ws" << endl;
    char c = file.peek();
    while(isspace(c))
    {
        file.get();
        c = file.peek();
    }
}

string getAttrName()
{
    cout << "get attr name" << endl;
    return "name";
}

string getAttrVal()
{
    cout << "get attr val" << endl;
    return "val";
}

struct Tag
{
    string name;
    vector<Attr> attrs;
};

Tag parseTag()
{
    cout << "parse tag " << endl;
    Tag tag;
    assert(file.get() == '<');
    // parse tag name.
    char c = file.get();
    while(isalnum(c))
    {
        tag.name += c;
        c = file.get();
    }
    cout << "tag name = " << tag.name << endl;
    skipWS();
    if(c == '>')
        return tag;
    // parse attributes.
    cout << "parse attributes" << endl;
    while(c != '>')
    {
        Attr attr;
        attr.name = getAttrName();
        c = '=';
        assert(c == '=');
        attr.val = getAttrVal();
        cout << "attr: name = " << attr.name << " = " << attr.val << endl;
    }
    return tag;
}

EltNode *parseEltNode()
{
    cout << "parse elt node" << endl;
    EltNode elt_node;
    Tag opening = parseTag();
    parseNodes();
    cout << "parse closing tag" << endl;
    Tag closing = parseTag();
    return new EltNode(elt_node);
}

TextNode *parseTextNode()
{
    cout << "parse text node" << endl;
    TextNode text_node;
    char c = file.peek();
    while(c != '<')
    {
        text_node.data += file.get();
        c = file.peek();
    }
    cout << "data = " << text_node.data << endl;
    return new TextNode();
}

vector<Node *> parseNodes()
{
    vector<Node *> roots;
    while(file)
        // TODO There might be text node as well..
        roots.push_back(parseEltNode());
    return roots;
}

int main()
{
    char c = file.peek();
//        cout << c;
    if(c != '<')
    {
        cout << "Not a valid node" << endl;
        exit(EXIT_FAILURE);
    }
    vector<Node *> roots = parseNodes();
    if(roots.empty())
    {
        cout << "Issue" << endl;
        exit(EXIT_FAILURE);
    }
    for(size_t i = 0; i < roots.size(); ++i)
        print(roots[0]);
}
