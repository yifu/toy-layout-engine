
#include <iostream>
#include <fstream>
#include <string>
#include "node.hpp"

using namespace std;

ifstream file("./test.html");

Node* parseNode()
{
    return new EltNode;
}

int main()
{
    while(file)
    {
        char c;
        file.get(c);
//        cout << c;
        if(c == '<')
            parseNode();
    }
}
