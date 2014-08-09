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
};

struct TextNode : public Node
{
    string data;
};

int main()
{
    cout << "hello toy.\n";
    TextNode text1;
    text1.data = "toto";
}
