#ifndef G3_TEST_VECTOR_X_D
#define G3_TEST_VECTOR_X_D

#include <iostream>

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


}

#endif
