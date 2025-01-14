#include "Reflect.h"

namespace reflect
{

    //--------------------------------------------------------
    // A type descriptor for int
    //--------------------------------------------------------

    struct TypeDescriptor_Int : TypeDescriptor
    {
        TypeDescriptor_Int() : TypeDescriptor{"int", sizeof(int)}
        {
        }
        virtual void dump(const void *obj, int /* unused */) const override
        {
            std::cout << "int{" << *(const int *)obj << "}";
        }
    };

    template <>
    TypeDescriptor *getPrimitiveDescriptor<int>()
    {
        static TypeDescriptor_Int typeDesc;
        return &typeDesc;
    }

    //--------------------------------------------------------
    // A type descriptor for double
    //--------------------------------------------------------
    struct TypeDescriptor_Double : TypeDescriptor
    {
        TypeDescriptor_Double() : TypeDescriptor{"double", sizeof(double)}
        {
        }

        virtual void dump(const void *obj, int /* unused */) const override
        {
            std::cout << "double{" << *(const double *)obj << "}";
        }
    };

    template <>
    TypeDescriptor *getPrimitiveDescriptor<double>()
    {
        static TypeDescriptor_Double typeDesc;
        return &typeDesc;
    }

    //--------------------------------------------------------
    // A type descriptor for std::string
    //--------------------------------------------------------

    struct TypeDescriptor_StdString : TypeDescriptor
    {
        TypeDescriptor_StdString() : TypeDescriptor{"std::string", sizeof(std::string)}
        {
        }
        virtual void dump(const void *obj, int /* unused */) const override
        {
            std::cout << "std::string{\"" << *(const std::string *)obj << "\"}";
        }
    };

    template <>
    TypeDescriptor *getPrimitiveDescriptor<std::string>()
    {
        static TypeDescriptor_StdString typeDesc;
        return &typeDesc;
    }

} // namespace reflect
