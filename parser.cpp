
#include <iostream>
#include <fstream>
#include <string>
#include "node.hpp"
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

ifstream file("./test.html");

void skipeWhiteChars()
{
    // TODO
}

string getName()
{
    // TODO Consume next word.
    return "name";
}

string getVal()
{
    return "val";
}

Node *parseNode()
{
    assert(file.get() == '<');
    EltNode node;
    // parse tag name.
    char c = file.get();
    while(isalpha(c))
    {
        node.tag_name += c;
        c = file.get();
    }
    skipeWhiteChars();
    if(c == '>')
        return new EltNode(node);
    // parse attributes.
    while(c != '>')
    {
        string name = getName();
        c = '=';
        assert(c == '=');
        string val = getVal();
        cout << "attr: name = " << name << " = " << val << endl;
    }
    return new EltNode(node);
}

vector<Node *> parseNodes()
{
    vector<Node *> roots;
    while(file)
        roots.push_back(parseNode());
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
