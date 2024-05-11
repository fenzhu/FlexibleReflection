#include <vector>
#include "Reflect.h"

struct Self
{
    Self(void (*init)(Self *)) { init(this); }
    int k;
};

struct Node
{
    std::string key;
    int value;
    std::vector<Node> children;

    static Self a;
    static void inita(Self *a);

    REFLECT() // Enable reflection for this type
};

int main()
{
    // Create an object of type Node
    Node node = {"apple", 3, {{"banana", 7, {}}, {"cherry", 11, {}}}};

    // Find Node's type descriptor
    reflect::TypeDescriptor *typeDesc = reflect::TypeResolver<Node>::get();

    // Dump a description of the Node object to the console
    typeDesc->dump(&node);
    std::cout << std::endl
              << Node::a.k << std::endl;
    return 0;
}

Self Node::a{Node::inita};
void Node::inita(Self *a)
{
    a->k = 20;
}

// Define Node's type descriptor
REFLECT_STRUCT_BEGIN(Node)
REFLECT_STRUCT_MEMBER(key)
REFLECT_STRUCT_MEMBER(value)
REFLECT_STRUCT_MEMBER(children)
REFLECT_STRUCT_END()
