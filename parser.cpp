
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

Node* parseNode()
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
    return new EltNode(node);
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
    Node *root = parseNode();
    if(root == 0)
    {
        cout << "Issue" << endl;
        exit(EXIT_FAILURE);
    }
    print(root);
}
