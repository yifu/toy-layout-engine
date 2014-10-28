
#include <iostream>
#include <fstream>
#include <string>
#include "node.hpp"
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

int level = 0;

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
    string name;
    char c = file.peek();
    while(c != '=')
    {
        name += file.get();
        c = file.peek();
    }
    return name;
}

string getAttrVal()
{
    string val;
    char c = file.get();
    assert(c == '"');
    c = file.peek();
    while(c != '"')
    {
        val += file.get();
        c = file.peek();
    }
    assert(c == '"');
    file.get();
    return val;
}

struct Tag
{
    string name;
    vector<Attr> attrs;
};

Tag parseTag()
{
    skipWS();
    cout << "parse tag " << endl;
    Tag tag;
    char c = file.get();
    if(c != '<')
        cout << "ERROR, c = " << c << endl;
    assert(c == '<');
    if(file.peek() == '/')
        file.get();
    // parse tag name.
    c = file.get();
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
        c = file.get();
        assert(c == '=');
        attr.val = getAttrVal();
        cout << "attr: name = " << attr.name << ", val = " << attr.val << endl;
        skipWS();
        c = file.peek();
    }
    c = file.get();
    assert(c == '>');
    return tag;
}

EltNode *parseEltNode()
{
    cout << "parse elt node" << endl;
    EltNode elt_node;
    Tag opening = parseTag();
    elt_node.tag_name = opening.name;
    elt_node.children = parseNodes();
    cout << "parse closing tag" << endl;
    Tag closing = parseTag();
    if(closing.name != opening.name)
    {
        cout << "Tag name mismatch, " << opening.name << " and " << closing.name << endl;
    }
    else
    {
        cout << "closing tag is " << closing.name << endl;
    }
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
    return new TextNode(text_node);
}

vector<Node *> parseNodes()
{
    ++level;
    cout << "PARSE NODES LVL=" << level << endl;
    vector<Node *> roots;
    while(true)
    {
        // TODO Refactor that.
        skipWS();
        if(not file)
            return roots;
        char c = file.peek();
        if(c == '<')
        {
            c = file.get();
            char next = file.peek();
            if(next == '/')
            {
                file.putback(c);
                return roots;
            }
            else
            {
                file.putback(c);
                roots.push_back(parseEltNode());
            }
        }
        else
            roots.push_back(parseTextNode());
    }
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
