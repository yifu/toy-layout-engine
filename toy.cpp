#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Node
{
    vector<Node*> children;
    enum { Text, Elt } type;
};

class EltNode : public Node
{
    string tag_name;
    map<string, string> attr;
};

class TextNode : public Node
{
    string data;
};

int main()
{
    cout << "hello toy.\n";
}
