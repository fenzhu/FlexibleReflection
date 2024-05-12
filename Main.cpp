#include <vector>
#include <memory>

#include "Reflect.h"

struct Self
{
    Self(void (*init)(Self *)) { init(this); }
    int k;
};

struct Node
{
    std::string key;
    double value;
    std::vector<Node> children;

    static Self a;
    static void inita(Self *a);

    REFLECT() // Enable reflection for this type
};

struct NodeUniquePtr
{
    std::string key;
    double value;
    std::unique_ptr<NodeUniquePtr> next;

    REFLECT() // Enable reflection for this type
};

struct test
{
    std::string str;
    enum
    {
        a = 1,
        b = 3,
    };

    enum
    {
        c = 4,
        d = 2,
    };

    REFLECT()
};

class ClassText
{
private:
    int classInt;

public:
    ClassText(int a) : classInt(a)
    {
    }

    REFLECT();
};

// sizeof(Empty) == 1
class Empty
{
};

void Run()
{
    // static member a of type Self in struct Node
    std::cout << std::endl
              << Node::a.k << std::endl;

    std::cout << test::a << std::endl;
    std::cout << test::d << std::endl;

    std::cout << sizeof(Empty) << std::endl;
}

main()
{
    // Create an object of type Node
    Node node = {"apple", 3, {{"banana", 7, {}}, {"cherry", 11, {}}}};
    // Find Node's type descriptor
    reflect::TypeDescriptor *typeDesc = reflect::TypeResolver<Node>::get();
    // Dump a description of the Node object to the console
    typeDesc->dump(&node);

    // support for std::unique_ptr
    NodeUniquePtr nodePtr = {"apple", 3,
                             std::unique_ptr<NodeUniquePtr>{new NodeUniquePtr{"banana", 7,
                                                                              std::unique_ptr<NodeUniquePtr>{new NodeUniquePtr{"cherry", 11, nullptr}}}}};
    reflect::TypeDescriptor *ptrDesc = reflect::TypeResolver<NodeUniquePtr>::get();
    ptrDesc->dump(&nodePtr);

    test t = {"str1"};
    reflect::TypeDescriptor *testDesc = reflect::TypeResolver<test>::get();
    testDesc->dump(&t);

    ClassText c(999);
    reflect::TypeDescriptor *classDesc = reflect::TypeResolver<ClassText>::get();
    classDesc->dump(&c);

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

REFLECT_STRUCT_BEGIN(test)
REFLECT_STRUCT_MEMBER(str)
REFLECT_STRUCT_END()

REFLECT_STRUCT_BEGIN(ClassText)
REFLECT_STRUCT_MEMBER(classInt)
REFLECT_STRUCT_END()

REFLECT_STRUCT_BEGIN(NodeUniquePtr)
REFLECT_STRUCT_MEMBER(key)
REFLECT_STRUCT_MEMBER(value)
REFLECT_STRUCT_MEMBER(next)
REFLECT_STRUCT_END()