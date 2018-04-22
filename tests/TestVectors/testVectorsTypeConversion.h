#ifndef G3_TEST_VECTOR_TYPE_CONVERSION
#define G3_TEST_VECTOR_TYPE_CONVERSION

#include <vector>

#include <math/vector3i.h>
#include <math/vector3d.h>

#include <math/vector4d.h>
#include <math/vector4f.h>

using namespace g3;

namespace g3test
{
    void testVector3_typeConversion()
    {
        Vector3d vec3d(1, 2, 3);
        Vector3f vec3f(7, 8, 9);
        Vector3i vec3i(4, 5, 6);

        Vector3d v3d;
        Vector3f v3f;
        Vector3i v3i;
        
        v3d = vec3f;
        v3d = vec3i;

        v3f = vec3d;
        v3f = vec3i;

        // v3i = vec3d;  // not support
        // v3i = vec3f;  // not support

        std::vector<Vector3d> vec3dList;
        vec3dList.push_back(vec3f); vec3dList.push_back(vec3i);

        std::vector<Vector3f> vec3fList;
        vec3fList.push_back(vec3d); vec3fList.push_back(vec3i);
    }

    void testVector4_typeConversion()
    {
        Vector4d vec4d(1, 2, 3, 4);
        Vector4f vec4f(6, 7, 8, 9);


    }
}

#endif
