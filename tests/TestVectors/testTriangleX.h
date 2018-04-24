#ifndef G3_TEST_VECTOR_TRIANGLE_X
#define G3_TEST_VECTOR_TRIANGLE_X

#include <math/triangle2.h>
#include <math/triangle3.h>

#include "testUtil.h"

using namespace g3;

namespace g3test
{
    void testTriangleX_constructor_typeConv()
    {
        std::cout << "testTriangleX_constructor_typeConv :" << std::endl;

        std::cout << "->test constructor 2d :" << std::endl;

        Vector2d v2d1(0, 0), v2d2(1, 0), v2d3(0, 1);
        Vector2f v2f1(5, 6), v2f2(8, 9), v2f3(4, 7);

        Triangle2d t2d(v2d1, v2d2, v2d3);
        Triangle2f t2f(v2f1, v2f2, v2f3);
        Triangle2d t2dCopy(t2d);
        Triangle2f t2fCopy(t2f);

        printTriangle2(t2d, " *t2d");
        printTriangle2(t2f, " *t2f");
        printTriangle2(t2dCopy, " *t2dCopy");
        printTriangle2(t2fCopy, " *t2fCopy");

        std::cout << "->test type conv 2d :" << std::endl;
        t2dCopy = t2f;
        t2fCopy = t2d;
        printTriangle2(t2dCopy, " *t2dCopy");
        printTriangle2(t2fCopy, " *t2fCopy");

        std::cout << "->test constructor 3d :" << std::endl;

        Vector3d v3d1(0, 0, 0), v3d2(0, 1, 0), v3d3(0, 0, 1);
        Vector3f v3f1(5, 6, 0), v3f2(8, 0, 9), v3f3(0, 4, 7);

        Triangle3d t3d(v3d1, v3d2, v3d3);
        Triangle3f t3f(v3f1, v3f2, v3f3);
        Triangle3d t3dCopy(t3d);
        Triangle3f t3fCopy(t3f);

        printTriangle3(t3d, " *t3d");
        printTriangle3(t3f, " *t3f");
        printTriangle3(t3dCopy, " *t3dCopy");
        printTriangle3(t3fCopy, " *t3fCopy");

        std::cout << "->test type conv 3d :" << std::endl;
        t3dCopy = t3f;
        t3fCopy = t3d;
        printTriangle3(t3dCopy, " *t3dCopy");
        printTriangle3(t3fCopy, " *t3fCopy");

        std::cout << std::endl;
    }

    void testTriangleX_functions()
    {
        std::cout << "testTriangleX_functions :" << std::endl;
        Vector2d v2d1(0, 0), v2d2(1, 0), v2d3(0, 1);
        Vector2f v2f1(5, 6), v2f2(8, 9), v2f3(4, 7);
        Triangle2d t2d(v2d1, v2d2, v2d3);
        Triangle2f t2f(v2f1, v2f2, v2f3);
        printTriangle2(t2d, " *t2d");
        printTriangle2(t2f, " *t2f");

        Vector3d v3d1(0, 0, 0), v3d2(0, 1, 0), v3d3(0, 0, 1);
        Vector3f v3f1(5, 6, 0), v3f2(8, 0, 9), v3f3(0, 4, 7);
        Triangle3d t3d(v3d1, v3d2, v3d3);
        Triangle3f t3f(v3f1, v3f2, v3f3);
        printTriangle3(t3d, " *t3d");
        printTriangle3(t3f, " *t3f");

        std::cout << "->test pointAt():" << std::endl;
        auto p2d = t2d.pointAt(0.2, 0.3, 0.5);
        auto p2f = t2f.pointAt(0.2f, 0.3f, 0.5f);
        printVector2(p2d, " *t2d at 0.2, 0.3, 0.5");
        printVector2(p2f, " *t2f at 0.2, 0.3, 0.5");
        p2d = t2d.pointAt(Vector3d(0.2, 0.4, 0.4));
        p2f = t2f.pointAt(Vector3f(0.2f, 0.4f, 0.4f));
        printVector2(p2d, " *t2d at Vector3d(0.2, 0.4, 0.4)");
        printVector2(p2f, " *t2f at Vector3f(0.2, 0.4, 0.4)");

        auto p3d = t3d.pointAt(0.2, 0.3, 0.5);
        auto p3f = t3f.pointAt(0.2f, 0.3f, 0.5f);
        printVector3(p3d, " *t3d at 0.2, 0.3, 0.5");
        printVector3(p3f, " *t3f at 0.2, 0.3, 0.5");
        p3d = t3d.pointAt(Vector3d(0.2, 0.4, 0.4));
        p3f = t3f.pointAt(Vector3f(0.2f, 0.4f, 0.4f));
        printVector3(p3d, " *t3d at Vector3d(0.2, 0.4, 0.4)");
        printVector3(p3f, " *t3f at Vector3f(0.2, 0.4, 0.4)");

        std::cout << "->test BarycentricCoords():" <<std::endl;
        auto b2d = t2d.barycentricCoords(Vector2d(0.2, 0.2));
        auto b2f = t2f.barycentricCoords(Vector2f(5, 7));
        auto b3d = t3d.barycentricCoords(Vector3d(0.0, 0.2, 0.2));
        auto b3f = t3f.barycentricCoords(Vector3f(0.0, 0.0, 0.0));
        printVector3(b2d, " *t2d at Vector2d(0.2, 0.2)");
        printVector3(b2f, " *t2f at Vector2f(5, 7)");
        printVector3(b3d, " *t3d at Vector3d(0.0, 0.2, 0.2)");
        printVector3(b3f, " *t3f at Vector3f(0.0, 0.0, 0.0)");

        std::cout << std::endl;
    }
}

#endif
