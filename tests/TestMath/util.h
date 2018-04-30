#ifndef G3_TEST_MATH_UTIL
#define G3_TEST_MATH_UTIL

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

    template<typename AAB2>
    void printAAB2(const AAB2 &aab, const char *info)
    {
        std::cout << "AxisAlignedBox2 : " << info << std::endl;
        std::cout << " -> vadility : " << aab.valid() << std::endl;
        printVector2(aab.center(), " -> center");
        std::cout << " -> width : " << aab.width() << std::endl;
        std::cout << " -> height : " << aab.height() << std::endl;
        std::cout << " -> area : " << aab.area() << std::endl;
        std::cout << " -> diagonalLength : " << aab.diagonalLength() << std::endl;
        std::cout << " -> maxDim : " << aab.maxDim() << std::endl;
        std::cout << " -> minDim : " << aab.minDim() << std::endl;
        std::cout << " -> maxUnsignedCoordinate : " << aab.maxUnsignedCoordinate() << std::endl;
        printVector2(aab.diagonal(), " -> diagonal");
    }

    template<typename AAB2>
    void printAAB2Simple(const AAB2 &aab, const char *info)
    {
        std::cout << "AxisAlignedBox2 : " << info << std::endl;
        std::cout << " -> vadility : " << aab.valid() << std::endl;
        printVector2(aab.minCoordinate(), " -> mincoord");
        printVector2(aab.maxCoordinate(), " -> maxcoord");
        printVector2(aab.center(), " -> center");
        std::cout << " -> width : " << aab.width() << std::endl;
        std::cout << " -> height : " << aab.height() << std::endl;
    }
}

#endif
