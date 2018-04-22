#ifndef G3_TEST_VECTOR_UTIL
#define G3_TEST_VECTOR_UTIL

#include <iostream>

namespace g3test
{
    template<typename T>
    void printVector2(T vec, const char *str)
    {
        std::cout << str << "  :  ";
        std::cout << "vector x: " << vec.x() << "  y: " << vec.y() << std::endl;
    }

    template<typename T>
    void printVector3(T vec, const char *str)
    {
        std::cout << str << "  :  ";
        std::cout << "vector x: " << vec.x() << "  y: " << vec.y() << "  z: " << vec.z() << std::endl;
    }
}

#endif
