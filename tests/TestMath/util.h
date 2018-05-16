#ifndef G3_TEST_MATH_UTIL
#define G3_TEST_MATH_UTIL

#include <iostream>
#include <string>

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
        printVector2(aab.minCoordinate(), " -> mincoord");
        printVector2(aab.maxCoordinate(), " -> maxcoord");
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

    template<typename AAB3>
    void printAAB3(const AAB3 &aab, const char *info)
    {
        std::cout << "AxisAlignedBox3 : " << info << std::endl;
        std::cout << " -> vadility : " << aab.valid() << std::endl;
        printVector3(aab.minCoordinate(), " -> mincoord");
        printVector3(aab.maxCoordinate(), " -> maxcoord");
        printVector3(aab.center(), " -> center");
        std::cout << " -> width : " << aab.width() << std::endl;
        std::cout << " -> height : " << aab.height() << std::endl;
        std::cout << " -> depth : " << aab.depth() << std::endl;
        std::cout << " -> volume : " << aab.volume() << std::endl;
        std::cout << " -> diagonalLength : " << aab.diagonalLength() << std::endl;
        std::cout << " -> maxDim : " << aab.maxDim() << std::endl;
        std::cout << " -> minDim : " << aab.minDim() << std::endl;
        printVector3(aab.diagonal(), " -> diagonal");
        printVector3(aab.extents(), " -> extents");
        for (int i = 0; i < 8; ++i)
        {
            std::string str = std::string(" -> corner ") + std::to_string(i);
            printVector3(aab.corner(i), str.c_str());
        }
    }

    template<typename AAB3>
    void printAAB3Simple(const AAB3 &aab, const char *info)
    {
        std::cout << "AxisAlignedBox3 : " << info << std::endl;
        std::cout << " -> vadility : " << aab.valid() << std::endl;
        printVector3(aab.minCoordinate(), " -> mincoord");
        printVector3(aab.maxCoordinate(), " -> maxcoord");
        printVector3(aab.center(), " -> center");
        std::cout << " -> width : " << aab.width() << std::endl;
        std::cout << " -> height : " << aab.height() << std::endl;
        std::cout << " -> depth : " << aab.depth() << std::endl;
    }

    template<typename Mat2>
    void printMatrix2(const Mat2 &mat, const char *info)
    {
        std::cout << "Matrix2 : " << info << std::endl;
        printVector2(mat.row(0), " -> row 0");
        printVector2(mat.row(1), " -> row 1");
    }

    template<typename Mat3>
    void printMatrix3(const Mat3 &mat, const char *info)
    {
        std::cout << "Matrix3 : " << info << std::endl;
        printVector3(mat.row(0), " -> row 0");
        printVector3(mat.row(1), " -> row 1");
        printVector3(mat.row(2), " -> row 2");
    }
}

#endif
