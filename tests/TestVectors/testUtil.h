#ifndef G3_TEST_VECTOR_UTIL
#define G3_TEST_VECTOR_UTIL

#include <iostream>

namespace g3test
{
    template<typename T>
    inline void printVector2(const T &vec, const char *str)
    {
        if (str != nullptr) std::cout << str << "  :";
        std::cout << "  vector x: " << vec.x() << "  y: " << vec.y() << std::endl;
    }

    template<typename T>
    inline void printVector3(const T &vec, const char *str)
    {
        if (str != nullptr) std::cout << str << "  :";
        std::cout << "  vector x: " << vec.x() << "  y: " << vec.y() << "  z: " << vec.z() << std::endl;
    }

    template<typename T>
    inline void printTriangle2(const T &tri, const char *str)
    {
        if (str != nullptr) std::cout << str << "  :" << std::endl;
        printVector2(tri.v0(), "    v0");
        printVector2(tri.v1(), "    v1");
        printVector2(tri.v2(), "    v2");
    }

    template<typename T>
    inline void printTriangle3(const T &tri, const char *str)
    {
        if (str != nullptr) std::cout << str << "  :" << std::endl;
        printVector3(tri.v0(), "    v0");
        printVector3(tri.v1(), "    v1");
        printVector3(tri.v2(), "    v2");
    }
}

#endif
