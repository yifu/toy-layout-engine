#include <vector>
#include <string>
#include <stdint.h>

struct Selector
{
    std::string tag_name;
    std::string id;
    std::vector<std::string> class_name;
};

struct Color
{
    uint8_t r, g, b, a;
};

struct Length
{
    float len;
    enum { Px } unit;
};

struct Declaration
{
    std::string name;
    union
    {
        std::string keyword;
        Color col;
        Length len;
    } value;
};

struct Rule
{
    std::vector<Selector> selectors;
    std::vector<Declaration> declarations;
};

struct StyleSheet
{
    std::vector<Rule> rules;
};
