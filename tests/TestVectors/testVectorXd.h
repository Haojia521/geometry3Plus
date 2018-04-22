#ifndef G3_TEST_VECTOR_X_D
#define G3_TEST_VECTOR_X_D

#include "testUtil.h"

#include <math/vector2d.h>
#include <math/vector3d.h>
#include <math/vector4d.h>

using namespace g3;

namespace g3test
{
    void testVectorXd_constructors()
    {
        double v2[] {1.0, 2.0};
        double v3[] {1.0, 2.0, 3.0};
        double v4[] {1.0, 2.0, 3.0, 4.0};

        Vector2d vec2d1;
        Vector2d vec2d2(1.0, 2.0);
        Vector2d vec2d3(v2);
        Vector2d vec2d4(vec2d2);

        Vector3d vec3d1;
        Vector3d vec3d2(1.0, 2.0, 3.0);
        Vector3d vec3d3(v3);
        Vector3d vec3d4(vec3d2);

        Vector4d vec4d1;
        Vector4d vec4d2(1.0, 2.0, 3.0, 4.0);
        Vector4d vec4d3(v4);
        Vector4d vec4d4(vec4d2);
    }

    void testVector2d_operators()
    {
        Vector2d va(1, 2);
        Vector2d vb(3, 4);

        printVector2(va, "va");
        printVector2(vb, "vb");

        printVector2(-va, "-va");
        printVector2(va + vb, "va + vb");
        printVector2(va - vb, "va - vb");
        printVector2(va * vb, "va * vb");
        printVector2(va / vb, "va / vb");

        printVector2(va + 10, "va + 10");
        printVector2(va - 12, "va - 12");
        printVector2(va * 3, "va * 3");
        printVector2(va / 4, "va / 4");

        printVector2(10 + va, "10 + va");
        printVector2(3 * va, "3 * va");
        printVector2(4 / va, "4 / va");
    }

    void testVector3d_operators()
    {
        Vector3d va(1, 2, 4);
        Vector3d vb(6, 8, 10);

        printVector3(va, "va");
        printVector3(vb, "vb");

        printVector3(-va, "-va");
        printVector3(va + vb, "va + vb");
        printVector3(va - vb, "va - vb");
        printVector3(va * vb, "va * vb");
        printVector3(va / vb, "va / vb");

        printVector3(va + 10, "va + 10");
        printVector3(va - 12, "va - 12");
        printVector3(va * 3, "va * 3");
        printVector3(va / 4, "va / 4");

        printVector3(10 + va, "10 + va");
        printVector3(3 * va, "3 * va");
        printVector3(4 / va, "4 / va");
    }

    void testVector2d_fuctions()
    {
        Vector2d va(1, 2);
        Vector2d vb(3, 4);

        // TODO: write testing code
    }
}

#endif
