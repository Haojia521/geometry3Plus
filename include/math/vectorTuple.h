#ifndef G3_MATH_VECTOR_TUPLE
#define G3_MATH_VECTOR_TUPLE

#include <tuple>

#include <math/vector3d.h>

namespace g3
{
    typedef std::tuple<Vector3d, Vector3d>                     Vector3dTuple2;
    typedef std::tuple<Vector3d, Vector3d, Vector3d>           Vector3dTuple3;
    typedef std::tuple<Vector3f, Vector3f, Vector3f>           Vector3fTuple3;

    typedef std::tuple<Vector2d, Vector2d>                     Vector2dTuple2;
    typedef std::tuple<Vector2d, Vector2d, Vector2d>           Vector2dTuple3;
    typedef std::tuple<Vector2d, Vector2d, Vector2d, Vector2d> Vector2dTuple4;
}

#endif
